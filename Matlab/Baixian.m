clc;
clear;
Ts=1;
fai=0.5; %支持相占空比
xs=100;
xf=200;
zs=30;
h=40;

x=[];
z=[];
for t=0:0.01:Ts*fai
    sigma=2*pi*t/fai/Ts;
    xep=(xf-xs)*(sigma-sin(sigma))/(2*pi)+xs;
    zep=h*(1-cos(sigma))/2+zs;
    x=[x,xep];
    z=[z,zep];
end
plot (x,z);
axis equal;
