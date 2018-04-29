clc;
clear;
clear all;

fclose(instrfind);

s = serial('COM8');
set(s, 'BaudRate', 9600);
fopen(s);

Map = zeros(9,3);
hmo = heatmap(Map);
fprintf(s,'%c', 'r');
while 1
    for n = 1:10
        Map(n, :) = str2double(strsplit(fgetl(s), '\t'));
        heatmap(Map);
        colormap('jet')
    end
    snapnow
    drawnow
    fprintf(s,'%c', 'r');
end