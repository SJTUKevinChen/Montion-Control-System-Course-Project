% S-curve(position) generator
phi = pi / 2; % Total rotation angle(rad)
ta = 3; % Acceleration/Deceleration time
tm = 2; % Time running in constant speed

vm = phi / (ta + tm); % Max speed

cnt = 0;
t = 0:0.01:(2 * ta + tm);

for ti = 0:0.01:(2 * ta + tm)
    cnt = cnt + 1;
    if ti < ta / 2
        x(cnt) = x1(vm, ta, tm, ti);
    elseif ti < ta
        x(cnt) = x2(vm, ta, tm, ti);
    elseif ti < ta + tm
        x(cnt) = x3(vm, ta, tm, ti);
    elseif ti < ta + tm + ta / 2
        x(cnt) = x4(vm, ta, tm, ti);
    else
        x(cnt) = x5(vm, ta, tm, ti);
    end
end

plot(t, x);


% First half of the acceleration curve
function x = x1(vm, ta, tm, t)
    x = 2 * vm / (3 * ta^2) * t.^3; 
end

% Second half of the acceleration curve
function x = x2(vm, ta, tm, t)
    x = vm * t + 2 * vm * (ta - t).^3 / (3 * ta^2) - vm * ta / 2; 
end

% Constant speed
function x = x3(vm, ta, tm, t)
    x = vm * t - vm * ta / 2; 
end

% First half of the deceleration curve
function x = x4(vm, ta, tm, t)
    x = vm * t - 2 * vm * (t - ta - tm).^3 / (3 * ta^2) - vm * ta / 2; 
end

% Second half of the deceleration curve
function x = x5(vm, ta, tm, t)
    x = - 2 * vm * (2 * ta + tm - t).^3 / (3 * ta^2) + vm * ta + vm * tm;
end