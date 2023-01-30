% Ashley Roxana Res�ndiz S�nchez 
% 19 de Enero de 2023

% Programa para graficar los valores de los 6 canales del ADC enviados por 
% UART de la tiva hacia matlab 


clc
clear all
close all

serial = serialport('com8',9600);
muestras = 10000; %Cantidad de muestras que se quieren
i = 1;

datos = cell(1, 6); 
for k=1:6
    datos{k} = zeros(1, muestras);
end

%Formato de la gr�fica
figure('Name', 'Se�ales de 6 canales del ADC', 'NumberTitle', 'on','color',[1 1 1]); grid on; hold on;
title('Voltajes de 6 canales del ADC', 'FontName', 'Arial', 'FontSize', 12);
xlabel('time [s]', 'FontName', 'Arial', 'FontSize', 9);
ylabel('Amplitud', 'FontName', 'Arial', 'FontSize', 9);

%Limintes de la gr�fica
xlim([0 100]);
ylim([0 4]);

%Color de graficas 
adc_0 = animatedline('Color', 'r');
adc_1 = animatedline('Color', 'c');
adc_2 = animatedline('Color', 'g');
adc_3 = animatedline('Color', 'm');
adc_4 = animatedline('Color', 'b');
adc_5 = animatedline('Color', 'y');

legend("Channel 0", "Channel 1", "Channel 2", "Channel 3", "Channel 8", "Channel B");


while i<muestras
    %Para modificar limite en eje x y hacer una grafica movible 
    if mod(i,100) == 0 %Si i es multiplo de 100
       xlim([i i+100]);
    end
    
    %Para guardar valores
    valor = readline(serial); 
    
    %Convierte valor1(caracteres) a valores numericos
    Canal_7 = str2double(valor);
    Canal_5 = str2double(valor);
    Canal_3 = str2double(valor);
    Canal_2 = str2double(valor);
    Canal_4 = str2double(valor);
    Canal_8 = str2double(valor);

    
    %Hacer conversi�n
    voltaje_7 = (Canal_7(ith_entry)*3.3)/4096;
    voltaje_5 = (Canal_5(ith_entry)*3.3)/4096;
    voltaje_3 = (Canal_3(ith_entry)*3.3)/4096;
    voltaje_2 = (Canal_2(ith_entry)*3.3)/4096;
    voltaje_4 = (Canal_4(ith_entry)*3.3)/4096;
    voltaje_8 = (Canal_8(ith_entry)*3.3)/4096;

    %Graficar
    addpoints(adc_0, time(ith_entry), voltage_7);
    addpoints(adc_1, time(ith_entry), voltage_5);
    addpoints(adc_2, time(ith_entry), voltage_3); 
    addpoints(adc_3, time(ith_entry), voltage_2);
    addpoints(adc_4, time(ith_entry), voltage_4);
    addpoints(adc_5, time(ith_entry), voltage_8);
    drawnow;
    
    i = i+1;  
end



