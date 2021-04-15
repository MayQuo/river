extends StateMachine
class_name EntityStateMachine

var entity = null

func set_entity(ent):
	if ent != null:
		for s in states.values():
			s.set_entity(ent)
	entity = ent

func add_state(tag, new_state):
	.add_state(tag, new_state)
	if entity != null:
		states[tag].set_entity(entity)
