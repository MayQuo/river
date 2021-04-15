extends Node
class_name Inventory

var items = {}

signal item_added(id, amount)
signal item_removed(id, amount)
signal item_changed(id, amount)

signal item_removed_from_list(id)
signal item_new_in_list(id, amount)
signal item_changed_and_already_in_list(id, amount)

func add(item, amount = 1):
	match typeof(item):
		TYPE_INT:
			_add_item_by_id(item, amount)
		TYPE_STRING:
			_add_item_by_name(item, amount)
		_:
			assert("error: parameter item has wrong type")

func remove(item, amount = 1):
	match typeof(item):
		TYPE_INT:
			_remove_item_by_id(item, amount)
		TYPE_STRING:
			_remove_item_by_name(item, amount)
		_:
			assert("error: parameter item has wrong type")

func get_item(item):
	match typeof(item):
		TYPE_INT:
			if items.has(item):
				return ItemData.get_item(item)
		TYPE_STRING:
			var _id = (ItemData.get_items_by_name(item)[0] as ItemType).id
			if items.has(_id):
				return ItemData.get_item(_id)
		_:
			assert("error: parameter item has wrong type")
	return null

###############################################################################
func _add_item_by_id(id, amount):
	if items.has(id):
		items[id] += amount
		emit_signal("item_changed_and_already_in_list", id, amount)
	else:
		items[id] = amount
		emit_signal("item_new_in_list", id, amount)
	emit_signal("item_added", id, amount)
	emit_signal("item_changed", id, amount)

func _add_item_by_name(name, amount):
	var list = ItemData.get_items_by_name(name)
	if list.size > 1:
		print("warning: propably wrong item: more than 1 item was found!")
	var _id = (list[0] as ItemType).id
	_add_item_by_id(_id, amount)
	emit_signal("item_added", _id, amount)
	emit_signal("item_changed", _id, amount)

func _remove_item_by_id(id, amount):
	if items.has(id):
		items[id] -= amount
		emit_signal("item_changed_and_already_in_list", id, -amount)
	if items[id] <= 0:
		items.erase(id)
		emit_signal("item_removed_from_list", id)
	emit_signal("item_removed", id, amount)
	emit_signal("item_changed", id, -amount)

func _remove_item_by_name(name, amount):
	var list = ItemData.get_items_by_name(name)
	if list.size > 1:
		print("warning: propably wrong item: more than 1 item was found!")
	var _id = (list[0] as ItemType).id
	_remove_item_by_id(_id, amount)
	emit_signal("item_removed", _id, amount)
	emit_signal("item_changed", _id, -amount)
