--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 12/10/18
-- Time: 10:44 PM
-- To change this template use File | Settings | File Templates.
--

isCocking = false
cockDelay = 10
cockTimer = 0
shotDamage = 120
shotVelocity = 30
weaponState = "WS_STOWED"

function pressPrimaryFire()
    weaponState = "WS_FIRING_PRIMARY"
end

function releasePrimaryFire()
    weaponState = "WS_IDLE"
    cockTimer = cockDelay
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
        if(cockTimer <= 0) then
            local deviation = 5
            local dir = game.playerRotation + 180 + math.random(-deviation, deviation)
            game.cameraKick(dir, 37.5)
            local vx = game.cursorX - game.playerX - 4
            local vy = game.cursorY - game.playerY - 4
            local len = math.sqrt(vx*vx + vy*vy)
            game.addBullet(true, game.playerX, game.playerY, shotDamage, shotVelocity*vx/len, shotVelocity*vy/len, 1.5, "")
            cockTimer = cockDelay
            weaponState = "WS_IDLE"
        else
            cockTimer = cockTimer - 1
        end
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