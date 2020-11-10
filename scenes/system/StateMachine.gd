extends Node
class_name StateMachine

var states = {}
var parent = null
var current_state = null
var prev = null
var entity = null

signal state_changed(s)

func define_state(name: String, state) -> void:
	states[name] = state
	states[name].parent = self
	states[name].entity = entity

func change_state(name: String):
	current_state = states[name]
	current_state.init()
	emit_signal("state_changed", name)

func init():
	if not states.empty() and current_state == null:
		current_state = states.values()[0]
		current_state.entity = entity
		#current_state.init()
		
func update(delta):
	if current_state:
		current_state.update(delta)

func get(name: String):
	return states[name]
