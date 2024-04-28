% S-curve generator
clear;
clc;
phi = pi / 2; % Total rotation angle(rad)
ta = 3; % Acceleration/Deceleration time
tm = 2; % Time running in constant speed

vm = phi / (ta + tm); % Max speed

cnt = 0;
t = 0:0.01:(2 * ta + tm);

for ti = 0:0.01:(2 * ta + tm)
    cnt = cnt + 1;
    if ti < ta / 2
        v(cnt) = v1(vm, ta, tm, ti);
    elseif ti < ta
        v(cnt) = v2(vm, ta, tm, ti);
    elseif ti < ta + tm
        v(cnt) = v3(vm, ta, tm, ti);
    elseif ti < ta + tm + ta / 2
        v(cnt) = v4(vm, ta, tm, ti);
    else
        v(cnt) = v5(vm, ta, tm, ti);
    end
end

figure(1);
plot(t, v);
xlabel('time(s)');
ylabel('velocity(rad/s)');

% First half of the acceleration curve
function v = v1(vm, ta, tm, t)
    v = 2 * vm / ta^2 * t.^2; 
end

% Second half of the acceleration curve
function v = v2(vm, ta, tm, t)
    v = vm - 2 * vm / ta^2 * (ta - t).^2; 
end

% Constant speed
function v = v3(vm, ta, tm, t)
    v = vm; 
end

% First half of the deceleration curve
function v = v4(vm, ta, tm, t)
    v = vm - 2 * vm / ta^2 * (t - ta - tm).^2; 
end

% Second half of the deceleration curve
function v = v5(vm, ta, tm, t)
    v = 2 * vm / ta^2 * (2 * ta + tm - t).^2;
end
