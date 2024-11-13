% Nombre: Andrés Degollado Muñoz
% Asignatura: Proyecto 2.
% Estos son los parámetros de la ecuación diferencial estocástica
% Mu y sigma son las constantes de la EDE a resolver.
mu = 0.05;         
sigma = 0.05; 
% S0 es el valor inicial de S
S0 = 1; 
% Representa la condición inicial
S(1) = S0;
% Representa el tamaño del paso temporal.
dt = 0.25;
% Representa el tiempo total de simulación
T = 10; 
% Se construye el número de pasos temporales.
N = floor(T/dt);
% S es un vector de ceros de N entradas.
S = zeros(1, N+1);

% Estos son los parámetros del robot
% Representa el radio de las llantas (en metros).
r = 0.0325; 
% Describe la distancia entre las llantas (en metros).
L = 0.1;  
% Son las velocidad angulares de las llantas derecha e izquierda (en
% rad/s).
wr = 7.9796;          
wl = 8.0425;  
% Se aplica la expresión de la velocidad lineal.
V = r * (wr + wl) / 2; 
% Se aplica la expresión de la velocidad angular.
w = r * (wr - wl) / L; 
% Se crea un vector que describe la posición en x.
x = zeros(1, N+1);
% Se crea un vector que describe la posición en y.
y = zeros(1, N+1); 
% Se crea un vector que describe el ángulo.
theta = zeros(1, N+1);
% Se crea un vector que representa el tiempo.
t = 0:dt:T;    

% Se aplica el método de Euler Maruyama para la solución de la ecuación
% diferencial estocástica.
S = zeros(1, N+1);
S(1) = S0;
for i = 1:N
    dZ = sqrt(dt) * randn;
    S(i+1) = S(i) + S(i) * mu * dt + S(i) * sigma * dZ;
end

% Se ponen las condiciones iniciales en los tres vectores del modelo
% cinemático.
x(1) = 0; y(1) = 0; theta(1) = 0;

% Se simula el movimiento del robot a través del modelo cinemático.
for i = 1:N
    x(i+1) = x(i) + V * dt * cos(theta(i));
    y(i+1) = y(i) + V * dt * sin(theta(i));
    theta(i+1) = theta(i) + dt * w + S(i);
end

% Se muestra en la pantalla los valores de "x" y de "y".
disp(x);
disp(y);

% Se gráfica de la trayectoria del robot.
figure;
plot(x, y);
xlabel('x (m)');
ylabel('y (m)');
title('Trayectoria del robot');
axis equal;
