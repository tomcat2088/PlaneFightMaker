function update()
if bullet_gun_count > 0 then
	if target.gunShootTimer > 2 then
		target.gunShootTimer = 0
		bullet_gun_0:shootWithAngle(180,0)
	end
end
end
update()