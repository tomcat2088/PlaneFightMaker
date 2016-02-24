function update()
    positionX = target:getPositionX()
    positionY = target:getPositionY()
    positionY = positionY + target.ySpeed
positionX = positionX + target.xSpeed
    if positionY < 200 then
        target.ySpeed = -target.ySpeed
    end
if positionX < 100 or positionX > gameSession:getStageSizeWidth() - 100 then
target.xSpeed = -target.xSpeed
end
    local position = Point.new()
    position.x = positionX
    position.y = positionY
    target:setPosition(position)
end
update()