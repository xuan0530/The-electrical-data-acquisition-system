function serial_comm
    % 创建串口对象
    delete(instrfindall);
    s = serialport('COM14', 115200);
    % % % s.Terminator = 'CR/LF';
    
    % 创建图形界面
    figure('Name', '发射通道状态监视器', 'Position', [100 100 800 400]);
    channel_status = zeros(1, 10); % 存储通道状态
    bar_h = bar(channel_status);
    ylim([-0.1 1.1]);
    xlabel('通道号');
    ylabel('状态');
    title('发射通道状态实时显示');
    grid on;
    
    try
        % 打开串口
        fopen(s);
        disp('开始监视发射通道...');
        
        while true
            % 等待数据帧头
            % % % while ~strcmp(fgetl(s), '#TX_START')
            % % %     pause(0.01);
            % % % end
            while(1)
                astr=fgetl(s);
                idx=findstr(astr,'NEL');
                if(isempty(idx))
                    pause(0.01);
                else
                    break;
                end
            end
            
            % 读取通道状态
            status_line = fgetl(s);
            %%%%[channel, status] = strread(status_line, 'CHANNEL_%d,%s', 'delimiter', ',');
            
            % 更新状态数组
            idx1=find(status_line=='_');
            idx2=find(status_line==',');
            channel=str2num(status_line(idx1+1:idx2-1));
            data = str2num(status_line(idx2+1:end));
            % idx=findstr(status_line,'ON');
            % if(isempty(idx))            
            %     channel_status(channel + 1) = 0;
            % else
            %     channel_status(channel + 1) = 1;
            % end
            % 
            % % 更新显示
            % set(bar_h, 'YData', channel_status);
            % drawnow;
            
            % 等待帧尾
            % while(1)
            %     astr=fgetl(s);
            %     idx=findstr(astr,'X_E');
            %     if(isempty(idx))   
            %         pause(0.01);
            %     else
            %         break;
            %     end
            % end
        end
        
    catch e
        disp(['错误: ' e.message]);
    end
    
    % 关闭串口
    fclose(s);
    delete(s);
    clear s;
end