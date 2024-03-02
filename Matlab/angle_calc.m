% 设置参数
L1 = 61.74;
L2 = 80;
theta1_range = linspace(0, pi/2, 100); % 第一根杆角度范围，确保在第四象限


figure;
hold on;
xlabel('X轴');
ylabel('Y轴');
title('大腿和小腿的运动轨迹');
x2_trajectory = zeros(length(theta1_range), 100);  %在每个θ1下，都记录100个点
y2_trajectory = zeros(length(theta1_range), 100);

% 遍历第一根杆的角度范围
for i = 1:length(theta1_range)
    % 当前角度
    theta1 = theta1_range(i);
    
    % 计算第一根杆的顶点坐标
    x1 = L1 * cos(theta1);
    y1 = -L1 * sin(theta1);
    
    % 计算第二根杆的顶点坐标
    theta2 = linspace(0, 2*pi, 100); % 在每个第一根杆角度下遍历第二根杆的角度范围
    x2 = x1 + L2 * cos(theta1 + theta2);
    y2 = y1 - L2 * sin(theta1 + theta2);
    
    x2_trajectory(i, :) = x2; %记录数据
    y2_trajectory(i, :) = y2;
    
    plot(x1, y1, 'r-*', 'LineWidth', 4);
    plot(x2,y2, 'b-', 'LineWidth', 2); % 注意 transpose
    axis equal;

     pause(0.01);
end








