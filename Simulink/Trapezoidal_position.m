% Trapezodial generator
phi = pi / 2; % Total rotation angle(rad)
ta = 4; % Acceleration/Deceleration time
tm = 4; % Time running in constant speed

vm = phi / (ta + tm); % Max speed

cnt = 0;
t = 0:0.01:(2 * ta + tm + 4);

for ti = 0:0.01:(2 * ta + tm + 4)
    cnt = cnt + 1;
    if ti < 0
        x(cnt) = 0;
    elseif ti < ta
        x(cnt) = x1(vm, ta, tm, ti);
    elseif ti < ta + tm
        x(cnt) = x2(vm, ta, tm, ti);
    elseif ti < ta * 2 + tm
        x(cnt) = x3(vm, ta, tm, ti);
    else
        x(cnt) = phi;
    end
end

plot(t, x);

function x = x1(vm, ta, tm, t)
    x = vm / (2 * ta) * t^2;
end

function x = x2(vm, ta, tm, t)
    x = vm * ta / 2 + vm * (t - ta);
end

function x = x3(vm, ta, tm, t)
    x = vm * ta / 2 + vm * tm + vm * (t - ta - tm) - vm / (2 * ta) * (t - ta - tm)^2;
end