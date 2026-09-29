classdef flightMode < Simulink.IntEnumType
    %FLIGHTMODE  Flight phase output by the flightMode state transition
    %   table in navigation.slx.
    enumeration
        IDLE(0)
        BOOST(1)
        ACTIVE(2)
        LOCKOUT(3)
    end

    methods (Static)
        function retVal = getDefaultValue()
            retVal = flightMode.IDLE;
        end
    end
end
