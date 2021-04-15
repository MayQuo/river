extends PanelContainer
class_name InventoryUI

export(NodePath) var entity_path = null

onready var item_list: VBoxContainer = $VBox/ItemList
onready var item_ui: PackedScene = preload("res://scenes/ui/ItemUI.tscn")

var inventory: Inventory = null

func _ready():
	inventory = (get_node(entity_path) as Entity).inventory
	inventory.connect("item_changed", self, "_on_inventory_item_changed")
	inventory.connect("item_new_in_list", self, "_on_inventory_item_new_in_list")
	inventory.connect("item_changed_and_already_in_list", self, "_on_inventory_item_changed_and_already_in_list")

func _on_inventory_item_new_in_list(id, amount):
	var item = item_ui.instance()
	var node_name = "item_" + str(id)
	item.name = node_name
	item_list.add_child(item, false)
	
	var data = ItemData.get_item(id) as ItemType
	item.texture_item.texture = data.texture
	item.label_item_name.text = data.name
	item.label_item_amount.text = str(amount)

func _on_inventory_item_removed_from_list(id):
	var node_name = "item_" + str(id)
	var item = item_list.get_node(node_name)
	item_list.remove_child(item)
	item.queue_free()

func _on_inventory_item_changed_and_already_in_list(id, amount):
	var node_name = "item_" + str(id)
	var item = item_list.get_node(node_name) as ItemUI
	var last_amount = int(item.label_item_amount.text)
	item.label_item_amount.text = str(last_amount + amount)
