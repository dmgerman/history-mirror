/*
 * driver.c - centralized device driver management
 *
 */

#define DEBUG 0

#include <linux/device.h>
#include <linux/module.h>
#include <linux/errno.h>
#include "base.h"

#define to_dev(node) container_of(node,struct device,driver_list)

int driver_for_each_dev(struct device_driver * drv, void * data, 
			int (*callback)(struct device *, void * ))
{
	struct list_head * node;
	struct device * prev = NULL;
	int error = 0;

	get_driver(drv);
	spin_lock(&device_lock);
	list_for_each(node,&drv->devices) {
		struct device * dev = get_device_locked(to_dev(node));
		if (dev) {
			spin_unlock(&device_lock);
			error = callback(dev,data);
			if (prev)
				put_device(prev);
			prev = dev;
			spin_lock(&device_lock);
			if (error)
				break;
		}
	}
	spin_unlock(&device_lock);
	put_driver(drv);
	return error;
}

struct device_driver * get_driver(struct device_driver * drv)
{
	struct device_driver * ret = drv;
	spin_lock(&device_lock);
	if (drv && drv->present && atomic_read(&drv->refcount) > 0)
		atomic_inc(&drv->refcount);
	else
		ret = NULL;
	spin_unlock(&device_lock);
	return ret;
}


void remove_driver(struct device_driver * drv)
{
	BUG();
}

/**
 * put_driver - decrement driver's refcount and clean up if necessary
 * @drv:	driver in question
 */
void put_driver(struct device_driver * drv)
{
	struct bus_type * bus = drv->bus;
	if (!atomic_dec_and_lock(&drv->refcount,&device_lock))
		return;
	list_del_init(&drv->bus_list);
	spin_unlock(&device_lock);
	BUG_ON(drv->present);
	driver_detach(drv);
	driver_remove_dir(drv);
	if (drv->release)
		drv->release(drv);
	put_bus(bus);
}

/**
 * driver_register - register driver with bus
 * @drv:	driver to register
 * 
 * Add to bus's list of devices
 */
int driver_register(struct device_driver * drv)
{
	if (!drv->bus)
		return -EINVAL;

	pr_debug("driver %s:%s: registering\n",drv->bus->name,drv->name);

	get_bus(drv->bus);
	atomic_set(&drv->refcount,2);
	rwlock_init(&drv->lock);
	INIT_LIST_HEAD(&drv->devices);
	drv->present = 1;
	spin_lock(&device_lock);
	list_add(&drv->bus_list,&drv->bus->drivers);
	spin_unlock(&device_lock);
	driver_make_dir(drv);
	driver_attach(drv);
	put_driver(drv);
	return 0;
}

void driver_unregister(struct device_driver * drv)
{
	spin_lock(&device_lock);
	drv->present = 0;
	spin_unlock(&device_lock);
	pr_debug("driver %s:%s: unregistering\n",drv->bus->name,drv->name);
	put_driver(drv);
}

EXPORT_SYMBOL(driver_for_each_dev);
EXPORT_SYMBOL(driver_register);
EXPORT_SYMBOL(driver_unregister);
EXPORT_SYMBOL(get_driver);
EXPORT_SYMBOL(put_driver);
