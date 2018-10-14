--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 13/10/18
-- Time: 3:46 PM
-- To change this template use File | Settings | File Templates.
--

cooldown = 0
isZooming = false
shotDamage = 500
shotVelocity = 40
weaponState = "WS_STOWED"

function pressPrimaryFire()
    weaponState = "WS_FIRING_PRIMARY"
end

function releasePrimaryFire()
    weaponState = "WS_IDLE"
end

function pressSecondaryFire()
    weaponState = "WS_FIRING_SECONDARY"
    isZooming = true
    return
end

function releaseSecondaryFire()
    weaponState = "WS_IDLE"
    isZooming = false
    return
end

function tick()
    if(weaponState == "WS_FIRING_PRIMARY") then
        if(cooldown <= 0) then
            local deviation = 5
            local dir = game.playerFacing + 180 + math.random(-deviation, deviation)
            game.cameraKick(dir, 80)
            local vx = game.cursorX - game.playerX - 4
            local vy = game.cursorY - game.playerY - 4
            local len = math.sqrt(vx*vx + vy*vy)
            game.addBullet(true, game.playerX, game.playerY,
                shotDamage, shotVelocity*vx/len, shotVelocity*vy/len, 5, "")
            cooldown = 60*0.5
            game.createAmmoCasing("res/pistol-particle.png", game.playerX, game.playerY, 0.5, 0, math.random(-5, 0), 0.5, 0.9, 60*3)
        end
    elseif(cooldown > 0) then
        cooldown = cooldown - 1
    end
    if(isZooming) then
        game.cameraSetFocus((game.cursorX + game.playerX)/2, (game.cursorY + game.playerY)/2)
    else
        game.cameraSetFocus(game.playerX, game.playerY)
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

