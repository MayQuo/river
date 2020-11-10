extends Node
class_name State

var parent = null
var entity = null

func init() -> void:
	pass
	
func update(delta) -> void:
	pass

func change_state(name: String) -> void:
	if parent:
		parent.change_state(name)
