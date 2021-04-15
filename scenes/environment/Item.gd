extends Area2D
class_name Item

onready var sprite = $Sprite
export(int) var id = 0

signal item_changed(id)
signal item_picked_up(actor)

func _ready():
	set_item(id)
	$AnimationPlayer.play("idle")
	
func _process(delta):
	pass

func set_item(item):
	match typeof(item):
		TYPE_INT:
			var i = ItemData.get_item(item)
			sprite.texture = i.texture
			id = i.id
			emit_signal("item_changed", id)
		TYPE_STRING:
			var i = (ItemData.get_items_by_name(item)[0] as ItemType)
			id = i.id
			sprite.texture = i.texture
			emit_signal("item_changed", id)

func collect(actor) -> int:
	emit_signal("item_picked_up", actor)
	var _id = id
	queue_free()
	return _id
