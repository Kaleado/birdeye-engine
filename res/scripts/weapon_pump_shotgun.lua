--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 13/10/18
-- Time: 12:10 AM
-- To change this template use File | Settings | File Templates.
--

pumpDelay = 5
pumpTimer = 0
pelletDamage = 30
pelletVelocity = 30
numPellets = 8
isPumping = false
isPumped = true
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
    if(isPumping) then
        pumpTimer  = pumpTimer - 1
        if(pumpTimer == 0) then
            isPumped = true
            isPumping = false
        end
    elseif(weaponState == "WS_FIRING_PRIMARY" and isPumped) then
        local deviation = 8
        local spread = 3
        local dir = game.playerRotation + 180 + math.random(-deviation, deviation)
        game.cameraKick(dir, 90)
        for x = 0, numPellets, 1
        do
            local vx = game.cursorX - game.playerX - 4
            local vy = game.cursorY - game.playerY - 4
            local len = math.sqrt(vx*vx + vy*vy)
            game.addBullet(true, game.playerX, game.playerY, pelletDamage,
                pelletVelocity*vx/len + math.random(-spread, spread), pelletVelocity*vy/len + math.random(-spread, spread), 1.5, "")
        end
        isPumped = false
        weaponState = "WS_IDLE"
    elseif(weaponState == "WS_FIRING_SECONDARY" and not isPumped) then
        game.createAmmoCasing("res/shotgun-particle.png", game.playerX, game.playerY,
            0.5, 0, math.random(-5, 0), 0.5, 0.9, 60*3)
        isPumping = true
        pumpTimer = pumpDelay
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

