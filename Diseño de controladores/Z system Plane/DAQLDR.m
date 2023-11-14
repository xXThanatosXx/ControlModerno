clc;
clear variables;
close all;

% Step one Simulation settings
initializeSimulation();

% Step two Generate step signal
u = generateStepSignal();

% Step three Configure and open serial port
port = configureSerialPort();

% Step four Send and receive data over serial port
y = communicateOverSerial(port, u);

% Step five Close and delete serial port
closeSerialPort(port);

% Step six Plot the results
plotResults(u, y);



% --- Helper Functions ---

function initializeSimulation()
    % Set simulation parameters
    global Ts tf t ta
    Ts = 0.05; % Sampling period in seconds
    tf = 5;    % Simulation duration in seconds
    t = 0:Ts:tf;
    ta = 1;
end

function u = generateStepSignal()
    global t ta
    % Generate step signal: 0 to 20 units in 5 seconds using array operations
    u = zeros(size(t));
    u(t > ta) = 20;
end

function port = configureSerialPort()
    % Serial port configuration
    com = 'COM3';
    delete(instrfind({'Port'},{com})); % Remove existing connections
    port = serial(com, 'Baudrate', 9600, ...
                  'StopBits', 1, ...
                  'DataBits', 8, ...
                  'Parity', 'none', ...
                  'Terminator', 'CR/LF', ...
                  'OutputBufferSize', 200, ...
                  'InputBufferSize', 200, ...
                  'Timeout', 5);
    fopen(port);
    pause(5);
end

function y = communicateOverSerial(port, u)
    global t Ts
    % Send the signal over the serial connection and record the response
    y = zeros(size(t));
    for k = 1:length(t)
        fprintf(port, '%s\n', num2str(u(k)), 'sync');
        y(k) = fscanf(port, '%f\n');
        pause(Ts);
    end
end

function closeSerialPort(port)
    fclose(port);
    delete(port);
end

function plotResults(u, y)
    global t
    % Plot the results
    figure;
    plot(t, y, 'b', t, u, 'r');
    xlabel('Time (s)');
    ylabel('%');
    legend('Y', 'U');
    grid on;
    % Save captured data 
    U = u'; %Input
    Y = y'; %output
    save('DataLDR','U','Y');
end

