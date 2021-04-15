extends Node

var items = {}

func _ready():
	add_item("herbs_prepared", preload("res://textures/sprites/items/item_herbs_prepared.png"), "refill one heart container", [1, 200, 50])
	add_item("food", null, "not bad", null)
	add_item("water", null, "pay attention", null)
	add_item("iron", null, "don't eat iron please", null)


func add_item(_name, _texture, _description, _values):
	var item = ItemType.new(items.size(), _name, _texture, _description, _values)
	items[items.size()] = item

func get_item(id) -> ItemType:
	if items.has(id):
		return items[id]
	else:
		assert("error: item not found in item data")
		return null

func get_items_by_name(name) -> Array:
	var _items = []
	for item in items.values():
		if item.name == name:
			_items.append(item)
	if _items.empty():
		assert("error: item not found in item data")
	return _items
