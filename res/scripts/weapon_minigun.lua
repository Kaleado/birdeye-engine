--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 13/10/18
-- Time: 4:10 PM
-- To change this template use File | Settings | File Templates.
--

minFireDelay = 0.03*60
maxFireDelay = 0.5*60
fireDelay = maxFireDelay
fireDelayDecreaseRate = 0.033*60
shotDamage = 21
shotVelocity = 13.0
speedMultiplier = 0.5

weaponState = "WS_STOWED"
cooldown = 0

function pressPrimaryFire()
    weaponState = "WS_FIRING_PRIMARY"
end

function releasePrimaryFire()
    weaponState = "WS_IDLE"
end

function pressSecondaryFire()
    weaponState = "WS_FIRING_SECONDARY"
    return
end

function releaseSecondaryFire()
    weaponState = "WS_IDLE"
    return
end

function tick()
    if(weaponState == "WS_FIRING_PRIMARY") then
        if(cooldown <= 0) then
            fireDelay = math.max(minFireDelay, fireDelay - fireDelayDecreaseRate)
            local dir = game.playerFacing + 180
            game.cameraKick(dir, 9.0)
            local dx = game.cursorX - game.playerX;
            local dy = game.cursorY - game.playerY;
            local distance  = math.sqrt(dx*dx + dy*dy)
            local deviation = distance/30;
            local vx = game.cursorX - 4 - game.playerX - math.random(-deviation, deviation)
            local vy = game.cursorY - 4 - game.playerY - math.random(-deviation, deviation)
            local len = math.sqrt(vx*vx + vy*vy)
            local speed = shotVelocity
            game.addBullet(true, game.playerX, game.playerY, shotDamage, speed*vx/len, speed*vy/len, 3.0, "")
            game.createAmmoCasing("res/pistol-particle.png", game.playerX, game.playerY, 0.5, 0, math.random(-5, 0), 0.5, 0.9, 60*3)
            cooldown = fireDelay
        else
            cooldown = cooldown - 1
        end
    elseif(weaponState == "WS_IDLE") then
        fireDelay = maxFireDelay
    end
end

function onEquip()
    return
end

function onUnequip()
    return
end

function onStow()
    weaponState = "WS_STOWED"
    return
end

function onUnstow()
    weaponState = "WS_IDLE"
    return
end