%% Perform analysis on data collected by the ISU Egg Drop Accelerometer

clear all;
close all;
% Prompt the user for the data file to analyze
[file, dir] = uigetfile('*.CSV', 'Select the file to analyze');


%% Read the data
% Open the datafile and read the first line containing the range setting
fileObject = fopen([dir filesep file]);

eval([fgetl(fileObject) ';']);    % The range is stored as an equation, so just parse it

% Read in the data, ignoring the range setting and column headers
rawData = textscan(fileObject, '%f%f%f', 'HeaderLines', 2, 'Delimiter', ',');

%% Process the data

% Compute the g per LSB value
gPerLSB = (range*2)/1024;

% Apply the scaling factor to the raw data from the sensor
xData = rawData{1,1}.*gPerLSB;
yData = rawData{1,2}.*gPerLSB;
zData = rawData{1,3}.*gPerLSB;
magData = sqrt(xData.^2 + yData.^2 + zData.^2);

%% Plot the data
figure;
subplot(4,1,1);
plot(xData);
ylim([-range range]);
ylabel('g-force');
title('X-Axis Data');

subplot(4,1,2);
plot(yData);
ylim([-range range]);
ylabel('g-force');
title('Y-Axis Data');

subplot(4,1,3);
plot(zData);
ylim([-range range]);
ylabel('g-force');
title('Z-Axis Data');

subplot(4,1,4);
plot(magData);
ylim([-range range]);
ylabel('g-force');
title('Vector Magnitude Data');
