--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 15/10/18
-- Time: 12:38 AM
-- To change this template use File | Settings | File Templates.
--

enemyState = "ES_IDLE"

hasAttacked = false
canLeap = true
leapCooldown = 0
leapDelayTimer = 0
leapTimer = 0
leaping = false
initiateLeap = false
returnHome = false
runOnce = false
tick = 60*3
aggroThreshold = 100
speed = 3
frames = {"res/anim0.png", "res/anim1.png", "res/anim2.png", "res/anim1.png", "res/anim0.png"}
home = enemy.position

math.randomseed(os.time())

function whenTick()
    if(enemyState == "ES_IDLE") then
        if(not returnHome and not runOnce) then
            enemy.velocity = Vector(math.random(-1, 1), math.random(-1, 1))
            runOnce = true
        elseif(returnHome and not runOnce) then
            local dx = home.x - enemy.position.x
            local dy = home.y - enemy.position.y
            local len = math.sqrt(dx*dx + dy*dy)
            enemy.velocity = Vector(dx/len, dy/len)
            runOnce = true
        end
        tick = tick - 1
        if(tick <= 0) then
            returnHome = not returnHome
            tick = 60*3
            runOnce = false
        end
        if(enemy:getDistanceFromPlayer() < aggroThreshold) then
            enemyState = "ES_AGGRO"
        end
    elseif(enemyState == "ES_ATTACKING") then
        if(hasAttacked == false) then
            enemy:setAnimation(frames, false, 10)
            enemy:startAnimation()
            enemy:addBullet(false, enemy.position.x, enemy.position.y, 10, 0, 0, 3.0, "")
        end
        if(enemy:finishedAnimation()) then
            hasAttacked = false
            enemyState = "ES_AGGRO"
        end
    elseif(enemyState == "ES_AGGRO") then
        local toPlayer = enemy:getVectorToPlayer()
        toPlayer.x = toPlayer.x * speed
        toPlayer.y = toPlayer.y * speed
        enemy.velocity = toPlayer

    end
end

function whenCollidingWith()
end

function whenKilled()
end

function whenDamaged()
end

-- Not necessary.

function whenAttacking()
end

function whenAggro()
end

function whenIdle()
end

