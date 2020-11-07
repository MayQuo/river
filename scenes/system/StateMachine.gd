extends Node
class_name StateMachine

onready var current_state_name: String = ""
onready var current_state: State = get_child(0)
onready var entity = self.get_parent()

var prev_state: String = "" setget ,get_prev

var states = {}

func _ready():
	pass

func _process(delta):
	if current_state:
		current_state.update(delta)

func change_state(next_state: String):
	if current_state_name == next_state:
		return
	# TODO: What happens if a state changed?
	# ISSUE: Player was locked in jump state and did not moved anywhere
	# 		 because previous state was equals to current state

	current_state.enter()

func get_prev() -> String:
	return prev_state
