% ���ò���
L = 61.74;          % �ȵĳ���
Ls =80;          %С�ȳ���
Tmax = 100; % ����֡��
theta_range = linspace(0, 2*pi,Tmax); % �Ƕȷ�Χ
theta_s_range= linspace(0, 2*pi,Tmax); % �Ƕȷ�Χ

Ts=1;
fai=0.5;

xs=-80;
xf=-1;
h=30;
zs=-115;

% ����ͼ�δ���
figure;

for t= 0:0.04:5
   t_mod = mod(t, 1); % ȡģ��ʹ t �� 0 �� 1 ֮��ѭ��
   if t_mod<Ts*fai 
       sigma=2*pi*t_mod/fai/Ts;
       zep=h*(1-cos(sigma))/2+zs;
       xep=(xf-xs)*(sigma-sin(sigma))/(2*pi)+xs;
       xep2=(xs-xf)*(sigma-sin(sigma))/(2*pi)+xf;
       y=zep;
       y2=zs;
   end
   if  t_mod>Ts*fai && t_mod<Ts 
       sigma=2*pi*(t_mod-(Ts*fai))/fai/Ts;
       zep=h*(1-cos(sigma))/2+zs;
       xep=(xs-xf)*(sigma-sin(sigma))/(2*pi)+xf;
       xep2=(xf-xs)*(sigma-sin(sigma))/(2*pi)+xs;
       y=zs;
       y2=zep;
   end
   
   sita_s = 2*pi - acos((xep.^2 + y.^2 - L.^2 - Ls.^2) / (2 * L * Ls));
   %С�ȷ���
   fail= acos((xep.^2 + y.^2 + L.^2 - Ls.^2) /(2 *L*sqrt(xep.^2+y.^2)));
   fail2=acos((xep2.^2 + y2.^2 + L.^2 - Ls.^2) /(2 *L*sqrt(xep2.^2+y2.^2)));
%    sita_rad = deg2rad(sita);
   if xep>0
       sita=abs(atan(y/xep))-fail;
   end
   if xep <0
       sita=pi-abs(atan(y/xep))-fail;
   end 
   if xep==0
       sita=pi-1.5707-fail;
   end
   if xep2>0
       sita2=abs(atan(y2/xep2))-fail2;
   end
   if xep2 <0
       sita2=pi-abs(atan(y2/xep2))-fail2;
   end 
   if xep2==0
       sita2=pi-1.5707-fail2;
   end
   Lx=L*cos(sita);
   Ly=L*sin(-sita);
   
   Lx2=L*cos(sita2);
   Ly2=L*sin(-sita2);
   
   small_legx=50+30*cos(sita_s);
   small_legy=50+30*sin(sita_s);
   
   clf; % ��յ�ǰͼ��
   hold on;
   
   sita_deg = rad2deg(sita);
   lower_sita_deg= rad2deg(sita_s);
   text(50, 0, ['\theta = ' num2str(sita_deg)], 'FontSize', 12);
   text(50, 20, ['\lower_theta = ' num2str(lower_sita_deg)], 'FontSize', 12);
   
   plot([0, Lx], [0, Ly], 'bo-', 'LineWidth', 20)
   plot([Lx,xep],[Ly,y],'ro-','LineWidth',15);
   
   plot([50, small_legx], [50, small_legy], 'bo-', 'LineWidth', 20)
   
   plot([0, Lx2], [0, Ly2], 'bo-', 'LineWidth', 20)
   plot([Lx2,xep2],[Ly2,y2],'ro-','LineWidth',15);
   
   
   center=[xep,y];
   center2=[xep2,y2];
   viscircles(center, 40, 'Color', 'g', 'LineWidth', 2);
   viscircles(center2, 40, 'Color', 'g', 'LineWidth', 2);
   %plot([Lx,xep],[Ly,y],'ro-','LineWidth',2);
   %plot([0, xep2], [0, y2], 'ro-', 'LineWidth', 4)
    % ���ȶ�������
   % thigh_x = L * cos(theta_range(T));
   % thigh_y = L * sin(theta_range(T));

    % С�ȶ�������
   % shin_x =thigh_x+ Ls * cos(theta_range(T));
   % shin_y =thigh_y+ Ls * sin(theta_range(T));
    
    
    
   
    
    % ���������᷶Χ
    axis([-100, 180, -140, 80]);

    % ��ӱ�ǩ�ͱ���
    xlabel('X��');
    ylabel('Z��');
    title('����������Ȳ��˶�����');
    axis equal;
    % ��ͣһС��ʱ�䣬�Ա�۲춯��Ч��
    pause(0.01);

end
