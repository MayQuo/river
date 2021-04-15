extends State
class_name StateMachine

var states = {}
var state: State = null
var prev_state: State = null

signal state_changed
signal state_entered
signal state_exited(old_state)

################################################################################
func enter():
	.enter()
	if state != null:
		state.enter()
		emit_signal("state_entered")
	pass

func update(delta):
	.update(delta)
	if state != null:
		state.update(delta)
	pass

func exit():
	if state != null:
		state.exit()
		emit_signal("state_exited", state)
	pass

################################################################################
func add_state(tag, new_state):
	states[tag] = new_state
	states[tag].parent = self
	states[tag].tag = tag
	if state == null:
		change_state(tag)
	pass

func remove_state(tag):
	states.erase(tag)
	pass

func change_state(tag):
	if states.empty() || not states.has(tag):
		return
		
	if states[tag] == state:
		return
		
	var next_state = states[tag]
	if next_state == null:
		return

	exit()
	
	prev_state = state
	state = next_state
	emit_signal("state_changed")
	enter()
	pass
################################################################################
