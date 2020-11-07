extends Node2D
class_name InputHandler

export(NodePath) var entity = null setget set_entity, get_entity

func _process(delta: float) -> void:
	if entity:
		input_update(delta)
		position = entity.position

func input_update(delta: float) -> void:
	pass

func set_entity(instance) -> void:
	entity = instance

func get_entity():
	return entity
