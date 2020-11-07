extends Node
class_name State

onready var state_machine = self.get_parent()
onready var entity = state_machine.get_parent()

func enter() -> void:
	pass

func update(delta: float) -> void:
	pass
