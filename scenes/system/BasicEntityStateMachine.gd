extends EntityStateMachine
class_name BasicEntityStateMachine

signal air_state_changed

const AIR = "air"

func _init():
	add_state(AIR, EntityStateMachineAir.new())
	change_state(AIR)
	
	states[AIR].connect("state_changed", self, "_on_air_state_changed")

func update(delta):
	if state == null:
		return
	.update(delta)

func _on_air_state_changed():
	emit_signal("air_state_changed")
