--
-- Created by IntelliJ IDEA.
-- User: kaleado
-- Date: 8/10/18
-- Time: 2:50 AM
-- To change this template use File | Settings | File Templates.
--

myPos = nil
targetVector = nil

function pressPrimaryFire()
    print("Press primary fire from "..myPos.x.." "..myPos.y.." to "..targetVector.x.." "..targetVector.y)
    return
end

function releasePrimaryFire()
    print("Release primary fire.")
    return
end

function pressSecondaryFire()
    print("Press secondary fire.")
    return
end

function releaseSecondaryFire()
    print("Release secondary fire.")
    return
end

function tick()
    return
end

function onEquip()
    print("Equip.")
    return
end

function onUnequip()
    print("Unequip.")
    return
end

function onStow()
    print("Stow.")
    return
end

function onUnstow()
    print("Unstowed.")
    return
end