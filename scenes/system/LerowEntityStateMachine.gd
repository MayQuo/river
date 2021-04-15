extends BasicEntityStateMachine
class_name LerowEntityStateMachine

const LADDER = "ladder"
var next_ladder = null

func _init():
	._init()
	add_state(LADDER, EntityStateMachineLadder.new())
	
	states[AIR].add_state("roll", EntityState.new())
	states[AIR].add_state("smoke", EntityState.new())
	
	states[AIR].connect("state_entered", self, "_on_air_state_entered")

func update(delta):
	.update(delta)

	if next_ladder != null and entity.get_ladder():
		if state.tag == AIR:
			state.change_state(state.FALL)
			change_state(LADDER)
			entity.velocity.x = 0
		elif state.tag == LADDER:
			change_state_to_air()

	if state.tag == AIR:
		var _air = state as EntityStateMachineAir
		
		if entity.get_roll():
			state.change_state("roll")
		if _air.state.tag == "roll":
			if not entity.animated_sprite.is_playing():
				_air.change_state(_air.FALL)
		if _air.state.tag == _air.IDLE and entity.get_smoke():
			var id: int = ItemData.get_items_by_name("herbs_prepared")[0].id
			var item = (entity.inventory as Inventory).get_item(id)
			if item != null and entity.health < entity.maximum_health:
				(entity.inventory as Inventory).remove(id)
				_air.change_state("smoke")
		if _air.state.tag == "smoke":
			entity.velocity.x = 0

func _on_air_state_entered():
	var _air = state as EntityStateMachineAir
	match state.state.tag:
		"roll":
			entity.animated_sprite.play("roll")
			yield(entity.animated_sprite,"animation_finished")
			entity.animated_sprite.stop()
			if state.tag != AIR:
				return
			elif _air.prev_state.tag == _air.JUMP:
				_air.start_falling_process()
			else:
				_air.change_state(_air.prev_state.tag)
		"smoke":
			entity.animated_sprite.play("smoke")
			yield(entity.animated_sprite,"animation_finished")
			(entity as Entity).health += 1
			entity.emit_signal("health_changed")
			_air.change_state(_air.IDLE)


func _on_Trigger_area_entered(area):
	if area.is_in_group("ladder"):
		next_ladder = area

func _on_Trigger_area_exited(area):
	if area.is_in_group("ladder"):
		change_state_to_air()
		next_ladder = null

func change_state_to_air():
	if state.tag == AIR:
		return
	
	change_state(AIR)
	if state is StateMachine:
		state.change_state(state.FALL)

func _on_Lerow_push_changed():
	entity.animation_tag_move = "push" if not entity.get_pushing() else "move"
	entity.animated_sprite.play(entity.animation_tag_move)
