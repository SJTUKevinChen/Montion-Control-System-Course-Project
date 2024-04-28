% Trapezodial generator
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
    if ti < 0
        v(cnt) = 0;
    elseif ti < ta
        v(cnt) = vm / ta * ti;
    elseif ti < ta + tm
        v(cnt) = vm;
    elseif ti < ta * 2 + tm
        v(cnt) = vm - vm / ta * (ti - tm - ta);
    else
        v(cnt) = 0;
    end
end

figure(1);
plot(t, v);
xlabel('time(s)');
ylabel('velocity(rad/s)');