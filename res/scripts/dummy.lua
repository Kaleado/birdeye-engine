--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 8/10/18
-- Time: 2:50 AM
-- To change this template use File | Settings | File Templates.
--

numShot = 0
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
            print("Number of bullets shot = "..numShot)
            local dir = game.playerRotation + 180
            game.cameraKick(dir, 13.0)
            local dx = game.cursorX - game.playerX;
            local dy = game.cursorY - game.playerY;
            local distance  = math.sqrt(dx*dx + dy*dy)
            local deviation = distance/10;
            local vx = game.cursorX - 4 - game.playerX - math.random(-deviation, deviation)
            local vy = game.cursorY - 4 - game.playerY - math.random(-deviation, deviation)
            local len = math.sqrt(vx*vx + vy*vy)
            local speed = 18
            numShot = numShot + 1
            game.addBullet(true, game.playerX, game.playerY, 1000, speed*vx/len, speed*vy/len, 1.5, "")
            cooldown = 0.07*60
        else
            cooldown = cooldown - 1
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