% ���ò���
L1 = 61.74;
L2 = 80;
theta1_range = linspace(0, pi/2, 100); % ��һ���˽Ƕȷ�Χ��ȷ���ڵ�������


figure;
hold on;
xlabel('X��');
ylabel('Y��');
title('���Ⱥ�С�ȵ��˶��켣');
x2_trajectory = zeros(length(theta1_range), 100);  %��ÿ����1�£�����¼100����
y2_trajectory = zeros(length(theta1_range), 100);

% ������һ���˵ĽǶȷ�Χ
for i = 1:length(theta1_range)
    % ��ǰ�Ƕ�
    theta1 = theta1_range(i);
    
    % �����һ���˵Ķ�������
    x1 = L1 * cos(theta1);
    y1 = -L1 * sin(theta1);
    
    % ����ڶ����˵Ķ�������
    theta2 = linspace(0, 2*pi, 100); % ��ÿ����һ���˽Ƕ��±����ڶ����˵ĽǶȷ�Χ
    x2 = x1 + L2 * cos(theta1 + theta2);
    y2 = y1 - L2 * sin(theta1 + theta2);
    
    x2_trajectory(i, :) = x2; %��¼����
    y2_trajectory(i, :) = y2;
    
    plot(x1, y1, 'r-*', 'LineWidth', 4);
    plot(x2,y2, 'b-', 'LineWidth', 2); % ע�� transpose
    axis equal;

     pause(0.01);
end








