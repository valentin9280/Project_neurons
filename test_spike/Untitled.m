n=1000;
dt=0.5;
T=ceil(1000/dt);
v = zeros(n,T);
u = zeros(n,T);
v(:,1)=-70;
u(:,1)=-14;
for t= 1:T-1;
dv =(0.04*v(:,t)+5).*v(:,t)+140-u(:,t);
end