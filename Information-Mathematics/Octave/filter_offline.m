%オフライン最小ニ乗法によるパラメータ推定
%format long
load 7prob_N.mat y2 % 観測データ
%load 7prob.mat y2 % 観測データ
period=2000
segment=period/1;
iteration=period/segment
%t=linspace(0,100,2001);            %観測値グラフ描画用時間ステップ
%t2=linspace(0,200,4001);          %推定値グラフ描画用時間ステップ
t=linspace(0,100,2001);            %観測値グラフ描画用時間ステップ
t2=linspace(0,200,4001);          %推定値グラフ描画用時間ステップ

for l=1:1:iteration
  for k=1:1:segment %データ数分だけループ
           if((segment*(1-1)+k)==1) x2=[0 0 1 0];
           elseif((segment*(1-1)+k)==2) x2=[y2(k-1,1) 0 0 1];
           else x2=[y2(k-1,1) y2(k-2,1) y2(k,2) y2(k-1,2)];
          endif

          if(k==1)
           X2=x2';
           else X2=[X2 x2']; % θを計算するための行列X2を作る
          endif
  endfor
  if(l==1) theta_hat = inv(X2*X2')*X2*y2((l-1)*segment+1:(l-1)*segment+segment,1);
  else  theta_hat = theta_hat .+ inv(X2*X2')*X2*y2((l-1)*segment+1:(l-1)*segment+segment,1);
  endif
endfor                         
  theta_hat ./= iteration
  

for(k=1:1:4000)
        if k>2
         u2 = u1;
         u1 =0;
          if k<=period
           zeta = [y_hat(1) y_hat(2) u2 u1];
          else
           zeta = [y_hat(1) y_hat(2) 0 0];
          endif
         y_hat=[zeta*theta_hat y_hat];           %グラフ描画用推定出力データ記録
        elseif k==1
         u1=1;
         zeta = [0 0 u1 0];
         y_hat =zeta*theta_hat;
        else
         zeta = [0 0 0 u1];
         y_hat =[zeta*theta_hat y_hat];
        endif
            %実際の出力は観測値y2(1000個)
endfor
%        plot(t(1:period),y2(1:period,1),"linewidth",5,t2(:,1:4000),y_hat(4000:-1:1),"linewidth",3);
%        plot(t2(:,1:4000),y_hat(4000:-1:1),"linewidth",3);
       %真のシステム出力と推定出力とを比較

