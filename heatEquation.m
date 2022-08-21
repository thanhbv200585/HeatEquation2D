T = 10;
M = 200;
N = 200;
dx = 0.1; dy = 0.1;
dt = 0.01;
D = 0.2;

C = zeros(M+2,N+2);
FD = zeros(M+2,N+2);
t = 0;
for i = 1 : M+2
    for j = 1:N+2
        if i > 1 && i < M+2 && j > 1 && j < N+2
            C(i,j) = 80.0;
        else C(i,j) = 25.0;
        end
    end
end

while t<T
    for i = 2:M+1
        for j = 2:N+1
            FD(i,j) = (C(i+1,j) - 2*C(i,j) + C(i-1,j))/(dx*dx) + (C(i,j+1) - C(i,j)*2 + C(i, j-1))/(dy*dy);
            C(i,j) = C(i,j) + D*dt*FD(i,j);
        end
    end
    
    for i = 1:M+2
        for j = 1:N+2
            if i > 1 && i < M+2 && j > 1 && j < N+2
            else C(i,j) = 25.0;
            end
        end
    end
    imagesc(C)
    colorbar
    drawnow
    t = t + dt;
end