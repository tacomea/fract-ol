# アプリの概要
フラクタルを表示するプログラムです！

# デモ
![demo.gif](https://github.com/tacomeet/fract-ol/blob/master/gif/demo.gif)

# 使用言語

これらのバージョンを開発中に使用。

- GNU make (version 3.81)
- GCC (Apple clang version 13.0.0)

# 機能（非機能）一覧

- 以下のフラクタルの表示
    - マンデルブロ集合
    - ジュリア集合（パラメータで使う数値を変更可能）
    - バーニングシップ
- マウスで指したポインターへのズームイン・アウト
- 十字キーを使用した移動
- 複数の色を使用し、フラクタルの深さを表現
- Ctrl+c、または、Escキーでプログラムを終了

# 注力した点

ズームをしていくと1回の描画にかかる計算量が増え、ズームがスムーズに行えなくなっていた。（マウススクロールを止めても、イベントの処理が残っているとそのままズームし続けてしまっていた。）それを解決するために、フレームをカウントし、描画が終わる前に受け取ったズームイベントは無視するようにした。その結果、ズームの切り替えや方向の転換がスムーズに行えるようになった。

```c
// hook.c
int	mouse_hook(int button, int x, int y, t_param *param)
{
	if ((button != MOUSE_UP && button != MOUSE_DOWN)
		|| param->var->frame == param->var->last_zoomed_frame)
		return (EXIT_FAILURE);
	...
}

int	loop_hook(t_param *param)
{
	param->var->frame++;
	return (EXIT_SUCCESS);
}
```

出来るだけ計算量が減るように記述しました

```c
// calculate.c

//int calc_burningship(t_var *var, double cr, double ci)
//{
//	double	zr;
//	double	zi;
//	double	zrn;
//	double	zin;
//	int		i;
//
//	zr = 0.0;
//	zi = 0.0;
//	i = 0;
//	while (zr * zr + zi * zi <= DIVERGE && i < var->imax)
//	{
//		zrn = zr * zr - zi * zi + cr;
//		zin = 2.0 * MOD(zr) * MOD(zi) + ci;
//		zr = zrn;
//		zi = zin;
//		i++;
//	}
//	return (i);
//}

int	calc_burningship(t_var *var, double cr, double ci)
{
	double	x;
	double	y;
	double	x2;
	double	y2;
	int		i;

	x = 0;
	y = 0;
	x2 = 0;
	y2 = 0;
	i = 0;
	while (x2 + y2 <= DIVERGE && i < var->imax)
	{
		y = 2.0 * fabs(x) * fabs(y) + ci;
		x = x2 - y2 + cr;
		x2 = x * x;
		y2 = y * y;
		i++;
	}
	return (i);
}
```

# 環境構築の手順

今回使用しているminilibxというライブラリを使用するために各種設定を行う必要があります。

詳しくは[こちら](https://github.com/42Paris/minilibx-linux/)をご覧ください！

```bash
git clone https://github.com/tacomeet/fract-ol --recursive
cd fract-ol
make
./fractol # ヘルプメッセージが出力されます
```

