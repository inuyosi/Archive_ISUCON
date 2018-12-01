load 7prob.mat y2 % 観測データ
t=linspace(0,100,2001); %観測値グラフ描画用時間ステップ
t2=linspace(0,200,4001);%推定値グラフ描画用時間ステップ
for k=1:1:1999 %データ数分だけループ
if(k==1) x2=[0 0 y2(k,2) 0];
elseif(k==2) x2=[y2(k-1,1) 0 0 y2(k-1,2)];
else x2=[y2(k-1,1) y2(k-2,1) y2(k,2) y2(k-1,2)];
endif
if(k==1)
X2=x2';
else X2=[X2 x2']; % θ計算用の行列X2を作る
endif
endfor
theta_hat = inv(X2*X2')*X2*y2(1:1999,1) % θを一括計算
