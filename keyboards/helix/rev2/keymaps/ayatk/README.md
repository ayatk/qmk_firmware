# ayatk keymap for helix

本キーマップは、Helix キーボードの 5 行版専用のキーマップです。

普通のキーボード使用者が、Helix キーボードを使うときになるべく違いが少なく戸惑いが少なくなるように意図したキーマップです。（意図通り成功しているかどうかは使用する人の判断で、、、)

## キー配置

以下に、Qwerty 配列時の、文字配列の図を示します。

![fig1](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3.png)

## レイヤー

| 優先順位 | 番号 | 名称       | 内容                                       |
| -------- | ---- | ---------- | ------------------------------------------ |
| 高い     | 9    | Adjust     | 機能キー（紫）                             |
|          | 8    | KFunction  | テンキーパッド用ファンクションキー類（青） |
|          | 7    | Extra char | 記号類（赤）                               |
|          | 6    | Function   | ファンクションキー類（青）                 |
|          | 3    | Keypad     | テンキーパッド配列                         |
|          | 2    | Dvorak     | Dvorak 配列                                |
|          | 1    | Colemak    | Colemak 配列                               |
| 低い     | 0    | Qwerty     | QWERTY 配列（ベース）                      |

Qwerty/Colemak/Dvorak/Keypad の各レイヤーは、後述する、Ajuest レイヤーの キーによる選択で、いずれか一つだけが有効になり、標準のキーマップとなります。

Function レイヤーは、下段両端の 4 つの Fn キーのどれかひとつを押している間だけ有効になり、矢印キー等のナビゲーションキーや F1, F2, ...F12 キーなどが配置されています。
上の図の青色の刻印のキーのあるレイヤーです。

Extra レイヤーは、下段中央部の Enter キーか BS キーを一定時間(0.2 秒)以上押していると押している間だけ有効になり、'+=-\_[]{}' の 8 つの記号と「英数」キー、「かな」キーが配置されています。
このため、Enter/BS キーで Enter/BS を入力するには、Enter/BS キーを押して短時間ですぐ離してください。
上の図の赤色の刻印のキーのあるレイヤーです。

Adjust レイヤーは、Adjust キーを押している間有効になります。
Adjust キーは Function レイヤーに有り、下段両端の 4 つの Fn キーのどれか一つを押しながら、下段中央部の Enter キーか BS キーを押すことで Adjust レイヤーが有効になります。
Adjust キー (Enter/BS)を押した後は、Fn キーは離して構いません。

### Adjust レイヤー

Ajust レイヤーは、LED のコントロール、Mac/Win モードの切り替え、Qwerty 配列, Colemak 配列, Dvorak 配列, TenkeyPad 配列の切り替えが行えます。

![fig2](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3adj.png)

### Mac モードと Win モード

キーボードには、Mac モードと、Win モードの二つのモードがあります。

現在のモードは OLED にアイコンとして表示されます。
(以下の指定キーは、Qwerty 配列時の文字を使ってキーを表示しています）

| コマンド   | 指定キー           | コード  |
| ---------- | ------------------ | ------- |
| Mac モード | Adjust + g(Qwerty) | AG_NORM |
|            | Adjust + h(Qwerty) |         |
| Win モード | Adjust + t(Qwerty) | AG_SWAP |
|            | Adjust + y(Qwerty) |         |

Mac モードと Win モードでは、Alt キーと Win(GUI)キーが入れ替わります。

Mac モードでは、Extra レイヤー の「英数」キーと「かな」キーで英語モードと日本語モードの切り替えができます。

Win モードでは、該当のキーはどちらも共に Alt + `（日本語 IME の切り替え）として入力されます。

### LED コントロール

バックライトや Underglow をコントロールするには Adjust レイヤーにある機能キーを使います。
(以下の指定キーは、Qwerty 配列時の文字を使ってキーを表示しています）

| コマンド       | 指定キー               | コード   |
| -------------- | ---------------------- | -------- |
| オン／オフ     | Adjust + e(Qwerty)     | RGB_TOG  |
|                | Adjust + i(Qwerty)     |          |
| モード切り替え | Adjust + d(Qwerty)     | RGB_SMOD |
|                | Adjust + k(Qwerty)     |          |
| 色相 +         | Adjust + Left Control  | RGB_HUI  |
|                | Adjust + Right Control |          |
| 色相 -         | Adjust + Left Shift    | RGB_HUD  |
|                | Adjust + Right Shift   |          |
| 彩度 +         | Adjust + ;(Qwerty)     | RGB_SAI  |
|                | Adjust + a(Qwerty)     |          |
| 彩度 -         | Adjust + z(Qwerty)     | RGB_SAD  |
|                | Adjust + /(Qwerty)     |          |
| 明度 +         | Adjust + s(Qwerty)     | RGB_VAI  |
|                | Adjust + l(Qwerty)     |          |
| 明度 -         | Adjust + x(Qwerty)     | RGB_VAD  |
|                | Adjust + >(Qwerty)     |          |
| リセット       | Adjust + w             | RGBRST   |

### 文字配列選択

Qwerty, Colemak, Dvorak, Keypad それぞれの文字配列の選択は以下のキーを使います。

| 選択配列 | 指定キー   |
| -------- | ---------- |
| Qwerty   | Adjust + 5 |
|          | Adjust + 6 |
| Calemak  | Adjust + 4 |
|          | Adjust + 7 |
| Dvorak   | Adjust + 3 |
|          | Adjust + 8 |
| Keypad   | Adjust + 2 |
|          | Adjust + 9 |

## テンキーパッドのキー配置

以下に、テンキーパッド配列時の、文字配列の図を示します。

![fig3](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/827632dda7db87cf88d41a0d3b476c5962c29213/helix-five_rows_r3key.png)

図でわかるように、テンキーと F1,F2..F12 のキー入力ができる配列です。
F12 キーは一定時間(0.2 秒)以上押していると KFunc キーとして働き、押している間は、青色の刻印のキー入力を行えます。
F12 そのものを入力するときは押して短時間ですぐ離してください。
F12 キーを押しているときは、F11 キー は Adjust キーとなり、Adjust レイヤーが有効になります。
これによって、Qwerty 配列などに戻すことが可能になります。

## 備考

本キーマップは、通常のキーボードの主要部分のホームポジション周辺をなるべくそのまま踏襲する方針で作成しました。
変更点は以下の通りです。

-   右手小指により多く割り当たっていた 5 つの記号と左上の 1 つの記号を中央に集め人差し指の担当とする。
-   Enter キーを親指担当として中央手前に移動。
-   Control キーを左右共にホームポジションの行に移動。
-   左手親指に BackSpace キーを割り当てる。

![fig4](https://gist.github.com/mtei/c81a3688206aa50996339cb9ced4751d/raw/d6e9af7684c051de4744b9dee9cd96b762bf4e2d/five_rows_making2.jpg)
