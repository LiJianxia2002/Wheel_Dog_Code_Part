% 设置参数
L = 61.74;          % 腿的长度
Ls =80;          %小腿长度
Tmax = 100; % 动画帧数
theta_range = linspace(0, 2*pi,Tmax); % 角度范围
theta_s_range= linspace(0, 2*pi,Tmax); % 角度范围

Ts=1;
fai=0.5;
% xs=-35;
% xf=65;
xs2=-10;
xf2=73;
h=35;
zs=-115;
% 创建图形窗口
figure;

for t= 0:0.04:5
   t_mod = mod(t, 1); % 取模，使 t 在 0 到 1 之间循环
   if t_mod<Ts*fai 
       sigma=2*pi*t_mod/fai/Ts;
       zep2=h*(1-cos(sigma))/2+zs;
       xep3=(xf2-xs2)*(sigma-sin(sigma))/(2*pi)+xs2;
       xep4=(xs2-xf2)*(sigma-sin(sigma))/(2*pi)+xf2;
       y3=zep2;
       y4=zs;
   end
   if  t_mod>Ts*fai && t_mod<Ts 
       sigma=2*pi*(t_mod-(Ts*fai))/fai/Ts;
       zep2=h*(1-cos(sigma))/2+zs;
       xep3=(xs2-xf2)*(sigma-sin(sigma))/(2*pi)+xf2;
       xep4=(xf2-xs2)*(sigma-sin(sigma))/(2*pi)+xs2;
       y3=zs;
       y4=zep2;
   end
   

   %plot([0, xep], [0, y], 'bo-', 'LineWidth', 2)
   fail3= acos((xep3.^2 + y3.^2 + L.^2 - Ls.^2) /(2 *L*sqrt(xep3.^2+y3.^2)));
   fail4= acos((xep4.^2 + y4.^2 + L.^2 - Ls.^2) /(2 *L*sqrt(xep4.^2+y4.^2)));
   if xep3>0
       sita3=abs(atan(y3/xep3))+fail3;
   end
   if xep3 <0
       sita3=pi-abs(atan(y3/xep3))+fail3;
   end 
   if xep3==0
       sita3=pi-1.5707+fail3;
   end
   
      if xep4>0
       sita4=abs(atan(y4/xep4))+fail4;
   end
   if xep4 <0
       sita4=pi-abs(atan(y4/xep4))+fail4;
   end 
   if xep4==0
       sita4=pi-1.5707+fail4;
   end
    
    
   Lx3=L*cos(sita3);
   Ly3=L*sin(-sita3);
   Lx4=L*cos(sita4);
   Ly4=L*sin(-sita4);
   
   clf; % 清空当前图形
   hold on;
   plot([0+149, Lx3+149], [0, Ly3], 'bo-', 'LineWidth', 20)
   plot([Lx3+149,xep3+149],[Ly3,y3],'ro-','LineWidth',15);
   plot([0+149, Lx4+149], [0, Ly4], 'bo-', 'LineWidth', 20)
   plot([Lx4+149,xep4+149],[Ly4,y4],'ro-','LineWidth',15); 
   
   center3=[xep3+149,y3];
   center4=[xep4+149,y4];
   viscircles(center3, 40, 'Color', 'g', 'LineWidth', 2);
   viscircles(center4, 40, 'Color', 'g', 'LineWidth', 2);
        % 添加标签和标题
    axis([-100, 300, -140, 20]);
    xlabel('X轴');
    ylabel('Z轴');
    title('四足机器人腿部运动动画');
     axis equal;
    % 暂停一小段时间，以便观察动画效果
    pause(0.01);
end

