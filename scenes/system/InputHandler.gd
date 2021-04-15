extends Node2D
class_name InputHandler

export(NodePath) var entity_node = null setget set_entity, get_entity
var entity

func _ready():
	entity = get_node(entity_node) as Entity

func _process(delta: float) -> void:
	if entity:
		input_update(delta)
		position = entity.position

func input_update(delta: float) -> void:
	pass

func set_entity(instance) -> void:
	entity_node = instance
	entity = get_node(entity_node) as Entity

func get_entity():
	return entity
