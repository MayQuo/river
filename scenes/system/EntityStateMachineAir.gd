extends EntityStateMachine
class_name EntityStateMachineAir

class _AirIdle extends EntityState:
	pass
class _AirMove extends EntityState:
	pass
class _AirJump extends EntityState:
	pass
class _AirFall extends EntityState:
	pass
class _AirLanding extends EntityState:
	pass

const IDLE = "idle"
const MOVE = "move"
const JUMP = "jump"
const FALL = "fall"
const LANDING = "landing"

func _init():
	connect("state_entered", self, "_on_state_entered")
	connect("state_exited", self, "_on_state_exited")
	
	add_state(IDLE, _AirIdle.new())
	add_state(MOVE, _AirMove.new())
	add_state(JUMP, _AirJump.new())
	add_state(FALL, _AirFall.new())
	add_state(LANDING, _AirLanding.new())
	
	change_state(IDLE)
	pass

func _on_state_entered():
	if entity == null:
		return
	match state.tag:
		IDLE:
			entity.animated_sprite.play(entity.animation_tag_idle)
		MOVE:
			entity.animated_sprite.play(entity.animation_tag_move)
		JUMP:
			entity.animated_sprite.play(entity.animation_tag_jump)
			entity.velocity.y = -entity.jump_height
			entity.coyote_timer.stop()
		FALL:
			entity.animated_sprite.play(entity.animation_tag_fall)
			entity.velocity.y = 0
		LANDING:
			entity.animated_sprite.play(entity.animation_tag_landing)
			yield(entity.animated_sprite, "animation_finished")
			if state.tag == LANDING:
				if entity.is_on_floor():
					if abs(entity.get_moving().x) > 0:
						change_state(MOVE)
					else:
						change_state(IDLE)
				else:
					change_state(FALL)
	pass

func start_falling_process():
	if not entity.coyote_timer.is_stopped():
		return
	entity.coyote_timer.start()
	yield(entity.coyote_timer, "timeout")
	if not entity.is_on_floor() and state.tag != JUMP:
		change_state(FALL)
	pass

func update(delta):
	if state == null or entity == null:
		return
	
	.update(delta)
	
	var dir = entity.get_moving().x
	entity.velocity.x = lerp(entity.velocity.x, entity.movement_speed * dir, entity.acceleration * delta)
	entity.velocity.y += entity.GRAVITY * delta * PI
	
	match state.tag:
		IDLE:
			if abs(entity.get_moving().x) > 0:
				change_state(MOVE) 
			if not entity.is_on_floor():
				start_falling_process()
			if entity.get_jumping():
				change_state(JUMP)
		MOVE:
			if entity.get_moving().x == 0:
				change_state(IDLE)
			if not entity.is_on_floor():
				start_falling_process()
			if entity.get_jumping():
				change_state(JUMP)
		JUMP:
			if entity.velocity.y >= 0:
				if entity.is_on_floor():
					if abs(entity.get_moving().x) > 0:
						change_state(MOVE)
					else:
						change_state(IDLE)
				else:
					change_state(FALL)
		FALL:
			if entity.is_on_floor():
				if not entity.jump_buffer.is_stopped():
					entity.jump_buffer.stop()
					change_state(JUMP)
				else:
					change_state(LANDING)
			elif entity.get_jumping():
				entity.jump_buffer.start()
		LANDING:
			if entity.is_on_floor():
				if entity.get_jumping():
					entity.jump_buffer.stop()
					change_state(JUMP)
	pass

func _on_state_exited(old_state):
	#match old_state.tag:
	#	FALL:
	#		entity.velocity.y = 0
	pass
