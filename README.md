
# Overview / 概要

A sketch for [M5Stack Core2](https://docs.m5stack.com/#/en/core/core2) .

m5core2_ancient_text_by_chatgpt is a program generate ancient document-like text for JRPG with [ChatGPT](https://chat.openai.com/) API.

\[日本語\]

[M5Stack Core2](https://docs.m5stack.com/#/en/core/core2) 用のスケッチです。

m5core2_ancient_text_by_chatgptは [ChatGPT](https://chat.openai.com/) APIを使ってRPGの古文書風のテキストを生成するプログラムです。

# Video / 動画

![video](video.gif)

# Installation / インストール

1. Login to [OpenAI API](https://platform.openai.com/) .

1. Click `Settings/Billing` in the left sidebar.

1. Click `Payment methods`.

1. Click `Add payment method`.

1. Fill the form.

1. Click `Add payment method` button.

1. Click `API Keys` in the left sidebar.

1. Make sure key has created. If it does not exist, create it and copy it.

1. Clone the repository:
    ```sh
    git clone https://github.com/cubic9com/m5core2_ancient_text_by_chatgpt.git
    cd m5core2_ancient_text_by_chatgpt
    ```

1. Install [Visual Studio Code](https://code.visualstudio.com/) if you haven't already.

1. Open the project using Visual Studio Code:
    ```sh
    code .
    ```

1. Change the `ssid` value and `password` value in `src/main.cpp` to match your network.

1. Change the `chatgpt_secret_key` value in `src/main.cpp` to match your OpenAPI secret key. 

1. Install `PlatformIO IDE` extension:
    - Go to the Extensions view (`Ctrl+Shift+X`).
    - Search for `PlatformIO IDE` and install it.

1. Open PlatformIO Home:
    - In the left Activity Bar, click PlatformIO icon.
    - In the left Primary Sidebar, go to `QUICK ACCESS > PIO Home > Open`.

1. Open the project:
    - In the right Editor Group, click `Open Project` in the `PIO HOME` tab.
    - Select the cloned `m5core2_ancient_text_by_chatgpt` project folder.

1. Build and upload the project:
    - In the left Primary Sidebar, go to `PROJECT TASKS > m5stack-core2 > General > Upload`.

\[日本語\]

1. [OpenAI API](https://platform.openai.com/) にログインします。

1. 左側のサイドバーで `Settings/Billing` をクリックします。

1. `Payment methods` をクリックします。

1. `Add payment method` をクリックします。

1. フォームに必要事項を入力します。

1. `Add payment method` ボタンをクリックします。

1. 左側のサイドバーで `API Keys` をクリックします。

1. キーが作成されていることを確認します。存在しない場合は、新しく作成してコピーしてください。

1. リポジトリをクローンします:
    ```sh
    git clone https://github.com/cubic9com/m5core2_ancient_text_by_chatgpt.git
    cd m5core2_ancient_text_by_chatgpt
    ```

1. まだインストールしていない場合は、[Visual Studio Code](https://code.visualstudio.com/) をインストールします。

1. Visual Studio Code でプロジェクトを開きます:
    ```sh
    code .
    ```

1. `src/main.cpp` 内の `ssid` の値と `password` の値をあなたのネットワークに合わせて変更します.

1. `src/main.cpp` 内の `chatgpt_secret_key` の値をあなたのOpenAIシークレットキーに合わせて変更します。 

1. `PlatformIO IDE` 拡張機能をインストールします:
    - 左サイドバーの「拡張機能」ビュー (`Ctrl+Shift+X`) を開きます。
    - `PlatformIO IDE` を検索してインストールします。

1. PlatformIO Home を開きます:
    - 左のアクティビティバーで PlatformIO アイコンをクリックします。
    - 左のメインサイドバーから `QUICK ACCESS > PIO Home > Open` を選択します。

1. プロジェクトを開きます:
    - 右のエディターグループ内の `PIO HOME` タブで `Open Project` をクリックします。
    - クローンした `m5core2_ancient_text_by_chatgpt` プロジェクトフォルダーを選択します。

1. プロジェクトをビルド＆アップロードします:
    - 左のメインサイドバーから `PROJECT TASKS > m5stack-core2 > General > Upload` を選択します。

# License / ライセンス

Copyright (C) 2023-2025, cubic9com All rights reserved.

This project is licensed under the MIT license.

See the `LICENSE` file for details.
