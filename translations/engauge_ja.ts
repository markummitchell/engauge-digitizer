<?xml version="1.0" encoding="UTF-8" ?><!DOCTYPE TS>
<TS language="ja_JP" version="2.1">
<context>
    <name>ChecklistGuide</name>
    <message>
        <location filename="../src/Checklist/ChecklistGuide.cpp" line="20" />
        <location filename="../src/Checklist/ChecklistGuide.cpp" line="21" />
        <source>Checklist Guide</source>
        <translation>チェックリストと手引き</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuide.cpp" line="22" />
        <source>Checklist Guide

This box contains a checklist of steps suggested by the Checklist Guide Wizard. Following these steps should produce a set of digitized points in an output file.

To run the Checklist Guide Wizard when an image file is imported, select the Help / Checklist Wizard menu option.</source>
        <translation>チェックリストと手引き

このボックスにはチェックリストと手引きウィザードで示される作業手順のチェックリストが含まれています。これらの手順に従い作業を進めることでデジタイズしたポイントをファイルとして出力することができます。

画像ファイルが読み込まれると同時にチェックリストと手引きウィザードが開始されるようにするにはヘルプ / チェックリストと手引きウィザード メニューにチェックを入れます。</translation>
    </message>
</context>
<context>
    <name>ChecklistGuidePageConclusion</name>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageConclusion.cpp" line="15" />
        <source>&lt;p&gt;A checklist guide has been created.&lt;/p&gt;&lt;br/&gt;&lt;br/&gt;&lt;br/&gt;&lt;p&gt;&lt;font color="red"&gt;Why does the imported image look different?&lt;/font&gt; After import, a filtered image is shown in the background. This filtered image is produced from the original image according to the parameters set in Settings / Color Filter. When the parameters have been set correctly, unimportant information (such as grid lines and background colors) has been removed from the filtered images so automated feature extraction can be performed. If desirable features have been removed from the image, the parameters can be adjusted using Settings / Color Filter, or the original image can be displayed instead using View / Background / Show Original Image.&lt;/p&gt;</source>
        <translation>&lt;p&gt;チェックリストと手引きが作成されました。&lt;/p&gt;&lt;br/&gt;&lt;br/&gt;&lt;br/&gt;&lt;p&gt;&lt;font color="red"&gt;インポートされた画像が全く違って見えることに気付いたでしょうか?&lt;/font&gt; インポート後、バックグラウンドとしてフィルタ処理を経た画像が表示されています。この画像は元の画像に対して 設定 / カラー フィルターメニューに指定されたパラメーターでフィルタ処理されて生成されたものです。 このパラメーターが正しくセットされている場合には、重要ではない情報 (例えばグリッド線やバックグラウンドの色合い) が除去され、図形の自動抽出を行うことが可能になります。もし抽出したい対象の図形も除去されてしまうようであれば、これらのパラメーターを 設定 / カラー フィルター で調整するか、あるいはビュー / バックグラウンド / オリジナル画像を表示する をメニューから選択することで、フィルター処理された画像のかわりに元の画像を表示することもできます。&lt;/p&gt;</translation>
    </message>
</context>
<context>
    <name>ChecklistGuidePageCurves</name>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="21" />
        <source>Curve name. Empty if unused.</source>
        <translation>カーブ 名。空欄のままにしておくこともできます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="22" />
        <source>Draw lines between points in each curve.</source>
        <translation>それぞれの カーブ のポイント間にラインを描画します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="23" />
        <source>Draw points in each curve, without lines between the points.</source>
        <translation>それぞれの カーブ のポイントを、ポイント 間のライン なしに描画します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="25" />
        <source>&lt;p&gt;What are the names of the curves that are to be digitized? At least one entry is required.&lt;/p&gt;</source>
        <translation>&lt;p&gt;これからデジタイズしようとするカーブに名前をつけてください。少なくとも一つのカーブ名が入力されている必要があります。&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="44" />
        <source>&lt;p&gt;How are those curves drawn?&lt;/p&gt;</source>
        <translation>&lt;p&gt;これらのカーブの表示方法を選択してください。 &lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="46" />
        <source>With lines (with or without points)</source>
        <translation>ライン表示 (ポイントを併せて表示する場合も含みます)</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageCurves.cpp" line="48" />
        <source>With points only (no lines between points)</source>
        <translation>ポイントのみ表示 (ポイント間にはラインが引かれません)</translation>
    </message>
</context>
<context>
    <name>ChecklistGuidePageIntro</name>
    <message>
        <location filename="../src/Checklist/ChecklistGuidePageIntro.cpp" line="15" />
        <source>&lt;p&gt;Engauge converts an image of a graph or map into numbers, as long as the image has axes and/or grid lines to define the coordinates.&lt;/p&gt;&lt;p&gt;This wizard creates a checklist of steps that can serve as a helpful guide. By following those steps, you can obtain digitized data points in an exported file. This wizard also provides a quick summary of the most useful features of Engauge.&lt;/p&gt;&lt;p&gt;New users are encouraged to use this wizard.&lt;/p&gt;</source>
        <translation>&lt;p&gt;Engauge はグラフや地図の画像を、それらが座標軸や位置座標を示すグリッドを持つ画像であればなんでも、数値化します&lt;/p&gt;&lt;p&gt;このウィザードではこれから行う作業の手順をチェックリストとして作成しますので、有用な手引きともなります。 これらの手順を追うことで、出力ファイルにはデジタイズされたデータをファイルとして出力することができます。このウィザードはまた Engaugeの最も便利な特長を知る簡単な概要ともなります。&lt;/p&gt;&lt;p&gt;初めて使い始める際にはぜひこのウィザードを利用してください。&lt;/p&gt;</translation>
    </message>
</context>
<context>
    <name>ChecklistGuideWizard</name>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="29" />
        <source>Checklist Guide Wizard</source>
        <translation>チェックリストと手引きウィザード</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="62" />
        <source>Curves</source>
        <translation>カーブ</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="106" />
        <source>Follow this checklist of steps to digitize your image. Each step will show a check when it has been completed.</source>
        <translation>このチェックリストにある手順に沿って画像をデジタイズします。それぞれの手順が完了しましたら、チェックボックスがマークされます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="107" />
        <source>The coordinates are defined by creating axis points:</source>
        <translation>座標は座標軸の基準となる点を新たに打っていくことで設定されます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="108" />
        <source>Add first of three axis points.</source>
        <translation>座標軸の基準となる3点のうち最初の点を追加します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="111" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="120" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="129" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="155" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="164" />
        <source>Click on</source>
        <translation>　</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="111" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="120" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="129" />
        <source>for &lt;b&gt;Axis Points&lt;/b&gt; mode</source>
        <translation>クリックして &lt;b&gt;座標軸の基準点&lt;/b&gt; モードにします。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="112" />
        <source>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates</source>
        <translation>座標軸の目盛またはグリッド線の交差するところでクリックします。座標の値が分かるように表示がされているものを選んでください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="113" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="122" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="131" />
        <source>Enter the coordinates of the axis point</source>
        <translation>座標軸の基準となる点の座標値を入力します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="114" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="123" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="132" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="185" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="213" />
        <source>Click on Ok</source>
        <translation>OK ボタンをクリックします</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="117" />
        <source>Add second of three axis points.</source>
        <translation>座標軸の基準となる3点のうち2番目の点を追加します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="121" />
        <source>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis point</source>
        <translation>座標軸の目盛またはグリッド線の交差するところでクリックします。座標の値が分かるように表示がされているものを選んでください。また基準とするほかの点からできるだけ離れた点を選びます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="126" />
        <source>Add third of three axis points.</source>
        <translation>座標軸の基準となる3点のうち3番目の点を追加します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="130" />
        <source>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis points</source>
        <translation>座標軸の目盛や、座標値ラベルの付いている 2 本のグリッド線の交点などで、互いに他の基準点から十分に離れたポイントをクリックします。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="137" />
        <source>Points are digitized along each curve:</source>
        <translation>ポイントをそれぞれのカーブに沿ってデジタイズしていきます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="149" />
        <source>Add points for curve</source>
        <translation>　</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="155" />
        <source>for &lt;b&gt;Segment Fill&lt;/b&gt; mode</source>
        <translation>&lt;b&gt;線分&lt;/b&gt; モードでカーブにポイントを追加していきます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="156" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="165" />
        <source>Select curve</source>
        <translation>ドロップダウン・リストからカーブを選択します</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="156" />
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="165" />
        <source>in the drop-down list</source>
        <translation>　</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="157" />
        <source>Move the cursor over the curve. If a line does not appear then adjust the &lt;b&gt;Color Filter&lt;/b&gt; settings for this curve</source>
        <translation>カーソルをカーブの位置に移動させます。もし ラインが現れないようでしたら、このカーブの &lt;b&gt;カラー フィルター&lt;/b&gt; 設定を調整してください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="159" />
        <source>Move the cursor over the curve again. When the &lt;b&gt;Segment Fill&lt;/b&gt; line appears, click on it to generate points</source>
        <translation>カーソル を再び カーブ の上に重ねます。 &lt;b&gt;線分&lt;/b&gt; がハイライトされたら、その上をクリックしてポイントを生成してください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="164" />
        <source>for &lt;b&gt;Point Match&lt;/b&gt; mode</source>
        <translation>&lt;b&gt;ポイント マッチ &lt;/b&gt; モード</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="166" />
        <source>Move the cursor over a typical point in the curve. If the cursor circle does not change color then adjust the &lt;b&gt;Color Filter&lt;/b&gt; settings for this curve</source>
        <translation>カーソル を 移動 し、対象の カーブ で典型的と思われる ポイント の位置に合わせてください。もしカーソルの円の色がそこで変らないようでしたら、 &lt;b&gt;カラー フィルター &lt;/b&gt; の設定を調整してください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="169" />
        <source>Move the cursor over a typical point in the curve again. Click on the point to start point matching</source>
        <translation>再度カーソル を 移動 し、対象の カーブ で典型的と思われる ポイント の位置に合わせてください。ポイント マッチング を開始する最初の点をクリックします。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="170" />
        <source>Engauge will display a candidate point. To accept that candidate point, press the right arrow key</source>
        <translation>Enguage が候補となるポイントを表示します。もしその候補のポイントで良ければ、右向きの矢印キーを押して確定してください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="171" />
        <source>The previous step repeats until you select a different mode</source>
        <translation>この手順は ほかのモードに切り替えられるまで 繰り返し実行できます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="179" />
        <source>The digitized points can be exported</source>
        <translation>この デジタイズされたポイントはエクスポートすることができます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="180" />
        <source>Export the points to a file</source>
        <translation>データポイントをファイルとしてエクスポートします。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="183" />
        <source>Select menu option &lt;b&gt;File / Export&lt;/b&gt;</source>
        <translation>メニューの &lt;b&gt;ファイル / エクスポート&lt;/b&gt;を選びます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="184" />
        <source>Enter the file name</source>
        <translation>ファイル名を入力</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="186" />
        <source>Congratulations!</source>
        <translation>完了です！</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="191" />
        <source>Hint - The background image can be switched between the original image and filtered image.</source>
        <translation>ヒントーバックグラウンド画像は元の画像とフィルタ処理された画像から切り替えて表示することができます。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="194" />
        <source>Select menu option &lt;b&gt;View / Background / Show Original Image&lt;/b&gt; to see the original image</source>
        <translation>オリジナルの画像を見るには &lt;b&gt;ビュー / バックグラウンド / オリジナルの画像を表示&lt;/b&gt; オプションをメニューから選択してください。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="195" />
        <source>Select menu option &lt;b&gt;View / Background / Show Filtered Image&lt;/b&gt; to see the image from &lt;b&gt;Color Filter&lt;/b&gt;</source>
        <translation>カラー フィルター で処理された画像を見るには &lt;b&gt;ビュー / バックグラウンド / フィルタ処理された画像を表示&lt;/b&gt; オプションを &lt;b&gt;メニューから選択してください。&lt;/b&gt;</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="210" />
        <source>Select menu option &lt;b&gt;Settings / Color Filter&lt;/b&gt;</source>
        <translation>&lt;b&gt;設定 / カラー フィルター&lt;/b&gt;オプションをメニューから選択します。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="211" />
        <source>Select the method for filtering. Hue is best if the curves have different colors</source>
        <translation>フィルタリングに利用する 手法 を選択します。 もしこれらの カーブ が異なる色で表現されていれば、色相 が最も良いオプションです。</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="212" />
        <source>Slide the green buttons back and forth until the curve is easily visible in the preview window</source>
        <translation>緑色の ボタン を前後にスライドさせて、プレビュー画面で カーブ が見やすくなるように調整してください。</translation>
    </message>
</context>
<context>
    <name>DlgAbout</name>
    <message>
        <location filename="../src/Dlg/DlgAbout.cpp" line="15" />
        <source>About Engauge</source>
        <translation>Engaugeについて</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgAbout.cpp" line="18" />
        <source>&lt;p&gt;Engauge Digitizer&lt;/p&gt;</source>
        <translation>&lt;p&gt;Engauge Digitizer&lt;/p&gt;</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgAbout.cpp" line="19" />
        <source>Version</source>
        <translation>バージョン</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgAbout.cpp" line="21" />
        <source>&lt;/p&gt;&lt;p&gt;&amp;copy; 2014 Mark Mitchell&lt;/p&gt;&lt;p&gt;Engauge Digitizer is an open source tool for efficiently extracting accurate numeric data from images of graphs. The process may be considered as "inverse graphing". When you "engauge" a document, you are converting pixels into numbers.&lt;/p&gt;&lt;p&gt;This is free software, and you are welcome to redistribute it under certain conditions according to the GNU General Public License Version 2,or (at your option) any later version.&lt;/p&gt;&lt;p&gt;Engauge Digitizer comes with ABSOLUTELY NO WARRANTY.&lt;/p&gt;&lt;p&gt;Read the included LICENSE file for details.&lt;/p&gt;&lt;p&gt;Engauge Digitizer Links&lt;p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='https://github.com/markummitchell/engauge-digitizer'&gt;Project Home Page&lt;/a&gt;&lt;/li&gt;&lt;li&gt;&lt;a href='https://gitter.im/markummitchell/engauge-digitizer'&gt;Gitter Forum&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;&lt;p&gt;FFTW 3.X.X Links&lt;/p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='http://www.fftw.org'&gt;Project page&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;&lt;p&gt;OpenJPEG 2.X Links&lt;/p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='http://www.openjpeg.org'&gt;Project page&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;</source>
        <translation>&lt;/p&gt;&lt;p&gt;&amp;copy; 2014 Mark Mitchell&lt;/p&gt;&lt;p&gt;Engauge Digitizer はグラフの画像から精密な数値データを効率的に抽出するためのオープンソース ツールです。この工程は  "inverse graphing"とも呼べるかも知れません。もしあなたがドキュメントと "engauge" ー Engaugeを通して携わる ー とき、あなたはピクセルを数値に変換しているのです。&lt;/p&gt;&lt;p&gt;これはフリーソフトであり、 GNU General Public License Version 2または(選択はお任せしますが)それ以降のライセンス条件に基づいて自由に再配布していただいて構いません。&lt;/p&gt;&lt;p&gt;Engauge Digitizer に関しては一切の保証を負いません。&lt;/p&gt;&lt;p&gt;詳細については同梱のLICENSE ファイルをお読みください。&lt;/p&gt;&lt;p&gt;Engauge Digitizer Links&lt;p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='https://github.com/markummitchell/engauge-digitizer'&gt;Project Home Page&lt;/a&gt;&lt;/li&gt;&lt;li&gt;&lt;a href='https://gitter.im/markummitchell/engauge-digitizer'&gt;Gitter Forum&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;&lt;p&gt;FFTW 3.X.X Links&lt;/p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='http://www.fftw.org'&gt;Project page&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;&lt;p&gt;OpenJPEG 2.X Links&lt;/p&gt;&lt;ul&gt;&lt;li&gt;&lt;a href='http://www.openjpeg.org'&gt;Project page&lt;/a&gt;&lt;/li&gt;&lt;/ul&gt;</translation>
    </message>
</context>
<context>
    <name>DlgEditPointAxis</name>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="64" />
        <source>Edit Axis Point</source>
        <translation>座標軸の基準となる ポイント を追加</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="107" />
        <source>Graph Coordinates</source>
        <translation>座標軸の基準点</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="116" />
        <source>as</source>
        <translation>以下の</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="126" />
        <source>(</source>
        <translation>(</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="134" />
        <source>Enter the first graph coordinate of the axis point.

For cartesian plots this is X. For polar plots this is the radius R.

The expected format of the coordinate value is determined by the locale setting. If typed values are not recognized as expected, check the locale setting in Settings / Main Window...</source>
        <translation>座標軸の基準となる3点のうち最初の点の座標を入力します。

直交座標のグラフの場合は Xを入力します。極座標のグラフの場合は半径 Rを入力します。

座標値をどのような形式で入力すべきかは ロケール により決まります。 もしタイプ入力してみた値が期待通りに認識されないようでしたら 設定 / メイン画面... から ロケール を確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="141" />
        <source>, </source>
        <translation>, </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="149" />
        <source>Enter the second graph coordinate of the axis point.

For cartesian plots this is Y. For polar plots this is the angle Theta.

The expected format of the coordinate value is determined by the locale setting. If typed values are not recognized as expected, check the locale setting in Settings / Main Window...</source>
        <translation>座標軸の基準となる3点のうち2番目の点の座標を入力します。

直交座標のグラフの場合は Yを入力します。極座標のグラフの場合は偏角 Theta を入力します。

座標値をどのような形式で入力すべきかは ロケール により決まります。 もしタイプ入力してみた値が期待通りに認識されないようでしたら 設定 / メイン画面... から ロケール を確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="156" />
        <source>)</source>
        <translation>)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="173" />
        <source>Number format</source>
        <translation>数字の表示形式</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="187" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointAxis.cpp" line="191" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgEditPointGraph</name>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="48" />
        <source>Edit Curve Point(s)</source>
        <translation>カーブ の ポイント を編集</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="90" />
        <source>Graph Coordinates</source>
        <translation>座標軸の基準点</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="99" />
        <source>as</source>
        <translation>以下の</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="107" />
        <source>(</source>
        <translation>(</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="115" />
        <source>Enter the first graph coordinate value to be applied to the graph points.

Leave this field empty if no value is to be applied to the graph points.

For cartesian plots this is the X coordinate. For polar plots this is the radius R.

The expected format of the coordinate value is determined by the locale setting. If typed values are not recognized as expected, check the locale setting in Settings / Main Window...</source>
        <translation>座標軸の基準となる3点のうち最初の点の座標を入力します。 

もしグラフのポイントに適用すべき値がない場合には、この欄を空白にしておいてください。
直交座標のグラフの場合は Xを入力します。極座標のグラフの場合は半径 Rを入力します。

座標値をどのような形式で入力すべきかは ロケール により決まります。もしタイプ入力してみた値が期待通りに認識されないようでしたら 設定 / メイン画面... から ロケール を確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="123" />
        <source>, </source>
        <translation>, </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="131" />
        <source>Enter the second graph coordinate value to be applied to the graph points.

Leave this field empty if no value is to be applied to the graph points.

For cartesian plots this is the Y coordinate. For polar plots this is the angle Theta.

The expected format of the coordinate value is determined by the locale setting. If typed values are not recognized as expected, check the locale setting in Settings / Main Window...</source>
        <translation>座標軸の基準となる3点のうち二つ目の点の座標を入力します。

もしグラフのポイントに適用すべき値がない場合には、この欄を空白にしておいてください。

 直交座標のグラフの場合は Y を入力します。極座標のグラフの場合は偏角 Thetaを入力します。

座標値をどのような形式で入力すべきかは ロケール により決まります。もしタイプ入力してみた値が期待通りに認識されないようでしたら 設定 / メイン画面... から ロケール を確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="139" />
        <source>)</source>
        <translation>)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="156" />
        <source>Number format</source>
        <translation>数字の表示形式</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="170" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditPointGraph.cpp" line="174" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgEditScale</name>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="51" />
        <source>Edit Axis Point</source>
        <translation>座標軸の基準となる ポイント を追加</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="80" />
        <source>Number format</source>
        <translation>数字の表示形式</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="94" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="98" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="110" />
        <source>Scale Length</source>
        <translation>スケールバー の長さ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgEditScale.cpp" line="122" />
        <source>Enter the scale bar length</source>
        <translation>スケールバー の長さを入力します。</translation>
    </message>
</context>
<context>
    <name>DlgErrorReportLocal</name>
    <message>
        <location filename="../src/Dlg/DlgErrorReportLocal.cpp" line="29" />
        <source>Error Report</source>
        <translation>エラー レポート</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportLocal.cpp" line="32" />
        <source>An unrecoverable error has occurred. Quitting.</source>
        <translation>修復できない エラー が発生しました。プログラムを終了します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportLocal.cpp" line="42" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
</context>
<context>
    <name>DlgErrorReportNetworking</name>
    <message>
        <location filename="../src/Dlg/DlgErrorReportNetworking.cpp" line="31" />
        <source>Error Report</source>
        <translation>エラー レポート</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportNetworking.cpp" line="34" />
        <source>An unrecoverable error has occurred. Would you like to send an error report to the Engauge developers?

The original document can be sent as part of the error report, which increases the chances of finding and fixing the problem(s). However, if any information is private then an anonymized version of the document will be sent.</source>
        <translation>修復できないエラーが発生しました。 エラー レポートを Engauge の開発グループに送りませんか ?

オリジナルのドキュメントを エラー レポートの一部として含めて送信することもでき、これは(時に複数の)問題を修正する手がかりとなると期待されます。しかしながら、私的な情報が含まれることもありますので、その場合は情報を秘匿したかたちでのドキュメントを送信します。 </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportNetworking.cpp" line="42" />
        <source>Include original document information, otherwise anonymize the information</source>
        <translation>オリジナルのドキュメント情報を含めます。これを選択しない場合にはドキュメント情報は秘匿されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportNetworking.cpp" line="54" />
        <source>Send</source>
        <translation>送信</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgErrorReportNetworking.cpp" line="59" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgImportAdvanced</name>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="18" />
        <source>Import Advanced</source>
        <translation>インポート（アドバンス）</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="49" />
        <source>Coordinate System Count:</source>
        <translation>座標系の数</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="55" />
        <source>Coordinate System Count

Specifies the total number of coordinate systems that will be used in the imported image. There can be one or more graphs in the image, and each graph can have one or more coordinate systems. Each coordinate system is defined by a pair of coordinate axes.</source>
        <translation>座標系の数

インポートした画像の読み取りに使われる座標系の総数を指定します。 画像には一つあるいは複数のグラフが含まれることもあり得ます。さらにそれぞれのグラフが一つまたはそれ以上の座標系からなることもあるでしょう。それぞれの座標系は2つの座標軸の組み合わせで表されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="63" />
        <source>Graph Coordinates Definition:</source>
        <translation>グラフ の座標系の設定：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="66" />
        <source>1 scale bar - Used for maps with a scale bar defining the map scale</source>
        <translation>1 つの スケールバー - マップ に縮尺を示す スケールバー が含まれる場合に使うことができます。 </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="67" />
        <source>The two endpoints of the scale bar will define the scale of a map. The scale bar can edited to set its length.

This setting is used when importing a map that has only a scale bar to define distance, rather than a graph with axes that define two coordinates.</source>
        <translation>スケールバー の両端を指定することで、マップ 上の縮尺を定めることができます。スケールバー の長さは入力された値に応じて変ります。

この設定は、インポート された マップ の画像に、通常の グラフ のような 2 点の座標を定義できる座標軸が含まれず、距離を示す スケールバー のみがあるような場合に使用します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="74" />
        <source>3 axis points - Used for graphs with both coordinates defined on each axis</source>
        <translation>座標軸の基準となる 3ポイント - 各軸上に 位置を示す 2つの座標値が得られるグラフ の場合に利用します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="76" />
        <source>Three axes points will define the coordinate system. Each will have both x and y coordinates.

This setting is always used when importing images in non-advanced mode.

In total, there will be three points as (x1,y1), (x2,y2) and (x3,y3).</source>
        <translation>座標軸上の 3 つの点で座標系を設定することができます。座標系はそれぞれ X 座標と Y 座標とを持つことになります。

アドバンス モードを選択しない場合には常にこの設定が使われます。

全体では、 (x1,y1)、(x2,y2)、(x3,y3)で表される 3 つの点が必要になります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="84" />
        <source>4 axis points - Used for graphs with only one coordinate defined on each axis</source>
        <translation>座標軸の基準となる 4ポイント - グラフ 上 の各軸上には座標値のうち 1 つしか値がない場合に利用します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportAdvanced.cpp" line="85" />
        <source>Four axes points will define the coordinate system. Each will have a single x or y coordinate.

This setting is required when the x coordinate of the y axis is unknown, and/or the y coordinate of the x axis is unknown.

In total, there will be two points on the x axis as (x1) and (x2), and two points on the y axis as (y1) and (y2).</source>
        <translation>座標軸上の4 つの点で座標系を設定することができます。座標系はそれぞれX 座標と Y 座標を持つことになります。

この設定は Y 軸が表示されている位置での X 座標が不明なとき、あるいは X 軸が表示されている位置での Y 座標が不明なときに利用できます。

全体では、 X 軸上に (x1) と (x2)の 2 点、Y 軸上に (y1) と (y2) の 2 点が必要になります。.</translation>
    </message>
</context>
<context>
    <name>DlgImportCroppingNonPdf</name>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingNonPdf.cpp" line="34" />
        <source>Image File Import Cropping</source>
        <translation>画像ファイルの一部をインポート</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingNonPdf.cpp" line="71" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingNonPdf.cpp" line="78" />
        <source>Preview window that shows what part of the image will be imported. The image portion inside the rectangular frame will be imported from the currently selected page. The frame can be moved and resized by dragging the corner handles.</source>
        <translation>プレビュー画面は画像のどの部分がインポートされるかを示しています。これは現在選択しているページの画像のうち、四角形をしたフレームの内側です。このフレームはコーナー ハンドルをマウスでドラッグすることで位置を動かしたりサイズを変更したりできます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingNonPdf.cpp" line="115" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingNonPdf.cpp" line="122" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgImportCroppingPdf</name>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="43" />
        <source>PDF File Import Cropping</source>
        <translation>PDF ファイルの一部をインポート</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="77" />
        <source>Page:</source>
        <translation>ページ：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="82" />
        <source>Page number that will be imported</source>
        <translation>インポートされるページ番号</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="100" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="107" />
        <source>Preview window that shows what part of the image will be imported. The image portion inside the rectangular frame will be imported from the currently selected page. The frame can be moved and resized by dragging the corner handles.</source>
        <translation>プレビュー画面は画像のどの部分がインポートされるかを示しています。これは現在選択しているページの画像のうち、四角形をしたフレームの内側です。このフレームはコーナー ハンドルをマウスでドラッグすることで位置を動かしたりサイズを変更したりできます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="151" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgImportCroppingPdf.cpp" line="158" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgRequiresTransform</name>
    <message>
        <location filename="../src/Dlg/DlgRequiresTransform.cpp" line="16" />
        <source>can only be performed after three axis points have been created, so the coordinates are defined</source>
        <translation>座標軸の設定のため、座標軸の3 つの基準点が指定された後に実行可能となります。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsAbstractBase</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsAbstractBase.cpp" line="99" />
        <source>Ok</source>
        <translation>Ok</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAbstractBase.cpp" line="107" />
        <source>Cancel</source>
        <translation>キャンセル</translation>
    </message>
</context>
<context>
    <name>DlgSettingsAxesChecker</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="39" />
        <source>Axes Checker</source>
        <translation>座標軸チェッカー</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="63" />
        <source>Axes Checker Lifetime</source>
        <translation>座標軸チェッカーの表示時間</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="70" />
        <source>Do not show</source>
        <translation>非表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="71" />
        <source>Never show axes checker.</source>
        <translation>常に座標軸チェッカーを非表示とします。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="74" />
        <source>Show for a number of seconds</source>
        <translation>座標軸チェッカーを指定秒数だけ表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="75" />
        <source>Show axes checker for a number of seconds after changing axes points.</source>
        <translation>座標軸の基準となる点を設定・変更した直後に、長さを秒で設定した期間だけ、座標軸チェッカーを表示します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="85" />
        <source>Show always</source>
        <translation>常に表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="86" />
        <source>Always show axes checker.</source>
        <translation>座標軸チェッカーを常に表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="95" />
        <source>Line color:</source>
        <translation>ラインの色：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="99" />
        <source>Select a color for the highlight lines drawn at each axis point</source>
        <translation>座標軸の基準点をハイライトする際の色を選択できます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="153" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsAxesChecker.cpp" line="160" />
        <source>Preview window that shows how current settings affect the displayed axes checker</source>
        <translation>プレビュー画面 では現在の設定がどのように 座標軸 チェッカー の表示に影響するかを確認することができます。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsColorFilter</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="37" />
        <source>Color Filter</source>
        <translation>カラー フィルター</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="62" />
        <source>Curve Name:</source>
        <translation>カーブ名：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="66" />
        <source>Name of the curve that is currently selected for editing</source>
        <translation>現在編集対象として選択されているカーブの名前</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="70" />
        <source>Filter mode:</source>
        <translation>フィルタリング モード</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="74" />
        <source>Filter the original image into black and white pixels using the Intensity parameter, to hide unimportant information and emphasize important information.

The Intensity value of a pixel is computed from the red, green and blue components as I = squareroot (R * R + G * G + B * B)</source>
        <translation>輝度に応じて元の画像をフィルタリングし、黒と白のピクセルにすることで、重要ではない情報は隠して重要な情報をより強調します。

ピクセルの輝度値は、red、green、blueの3つのカラーコンポーネントから I = squareroot (R * R + G * G + B * B)という計算式で得ています。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="82" />
        <source>Filter the original image into black and white pixels by isolating the foreground from the background, to hide unimportant information and emphasize important information.

The background color is shown on the left side of the scale bar.

The distance of any color (R, G, B) from the background color (Rb, Gb, Bb) is computed as F = squareroot ((R - Rb) * (R - Rb) + (G - Gb) * (G - Gb) + (B - Bb)). On the left end of the scale, the foreground distance value is zero, and it increases linearly to the maximum on the far right.</source>
        <translation>元の画像からフォアグラウンド色とバックグラウンド色を区別しそれぞれに黒と白のピクセルを適用することで、重要ではない情報は隠して重要な情報をより強調します。

バックグラウンド色はスケールバーの左側に表示されます。

全ての色 (R, G, B) について、バックグラウンド色 (Rb, Gb, Bb)からの色差が距離 F = squareroot ((R - Rb) * (R - Rb) + (G - Gb) * (G - Gb) + (B - Bb))として計算されます。スケールバーでの左端ではフォアグラウンド色の色差はゼロですが、スケールバー上を右へいくほど直線的に色差が増大し、右端で最大となります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="92" />
        <source>Filter the original image into black and white pixels using the Hue component of the Hue, Saturation and Value (HSV) color components, to hide unimportant information and emphasize important information.</source>
        <translation>色相 Hue、彩度 Saturation、明度 Valueからなる HSV 色空間 (HSV)で色を表現し、このなかの 色相 Hue 成分をもとに元の画像をフィルタリングし、黒と白のピクセルに区分することで、重要ではない情報は隠して重要な情報をより強調します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="99" />
        <source>Filter the original image into black and white pixels using the Saturation component of the Hue, Saturation and Value (HSV) color components, to hide unimportant information and emphasize important information.</source>
        <translation>色相 Hue、彩度 Saturation、明度 Valueからなる HSV 色空間(HSV)で色を表現し、このなかの 彩度 Saturation成分をもとに元の画像をフィルタリングし、黒と白のピクセルに区分することで、重要ではない情報は隠して重要な情報をより強調します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="106" />
        <source>Filter the original image into black and white pixels using the Value component of the Hue, Saturation and Value (HSV) color components, to hide unimportant information and emphasize important information.

The Value component is also called the Lightness.</source>
        <translation>色相 Hue、彩度 Saturation、明度 Valueからなる HSV 色空間 (HSV)で色を表現し、このなかの明度 Value成分をもとに元の画像をフィルタリングし、黒と白のピクセルに区分することで、重要ではない情報は隠して重要な情報をより強調します。

この明度 Value はまた Lightnessとも呼ばれます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="122" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="129" />
        <source>Preview window that shows how current settings affect the filtering of the original image.</source>
        <translation>プレビュー画面では、元の画像をフィルタリングするにあたって、現在の設定がどのような効果を与えているかを見ることができます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="144" />
        <source>Filter Parameter Histogram Profile</source>
        <translation>ヒストグラム上でのフィルター範囲調整</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="152" />
        <source>Histogram profile of the selected filter parameter. The two Dividers can be moved back and forth to adjust the range of filter parameter values that will be included in the filtered image. The clear portion will be included, and the shaded portion will be excluded.</source>
        <translation>選択されたフィルター対象成分をヒストグラムで表示しています。分割線 Dividerが2つ表示されており、それぞれ前後に動かすことでフィルターの範囲を調整することができ、フィルター後の出力画像に反映されます。明るい部分は出力に含められ、影が付けられている部分は除外されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsColorFilter.cpp" line="159" />
        <source>This read-only box displays a graphical representation of the horizontal axis in the histogram profile above.</source>
        <translation>このボックスは読み取り専用で、ヒストグラムの水平方向の軸を示しています。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsCoords</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="75" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="911" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="915" />
        <source>Coordinates</source>
        <translation>座標</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="214" />
        <source>Date/Time:</source>
        <translation>日付/時刻</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="224" />
        <source>Date format to be used for date values, and date portion of mixed date/time values, during input and output.

Setting the format to an empty value results in just the time portion appearing in output.</source>
        <translation>日付形式は出入力において日付を値とする場合および日付/時刻の日付部分に使われます。

日付形式を空欄にしておくと時刻部分のみが出力されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="231" />
        <source>Time format to be used for time values, and time portion of mixed date/time values, during input and output.

Setting the format to an empty value results in just the date portion appearing in output.</source>
        <translation>時刻形式は出入力において時刻を値とする場合および日付/時刻の時刻部分に使われます。

時刻形式を空欄にしておくと日付部分のみが出力されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="243" />
        <source>Coordinates Types</source>
        <translation>座標のタイプ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="248" />
        <source>Polar</source>
        <translation>極座標</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="248" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="914" />
        <source>R</source>
        <translation>動径 R</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="250" />
        <source>Cartesian (X, Y)</source>
        <translation>直交座標 (X, Y)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="251" />
        <source>Select cartesian coordinates.

The X and Y coordinates will be used</source>
        <translation>直交座標を選択します。

X と Y からなる座標が使われます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="257" />
        <source>Select polar coordinates.

The Theta and R coordinates will be used.

Polar coordinates are not allowed with log scale for Theta</source>
        <translation>極座標を選択します。

偏角 Theta と動径 R が使われます。

極座標を選択した場合、偏角Thetaに対数スケールを使うことはできません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="276" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="311" />
        <source>Scale:</source>
        <translation>軸目盛：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="279" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="314" />
        <source>Linear</source>
        <translation>リニア</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="280" />
        <source>Specifies linear scale for the X or Theta coordinate</source>
        <translation>X 軸または偏角の目盛をリニア軸とします。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="284" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="322" />
        <source>Log</source>
        <translation>対数</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="285" />
        <source>Specifies logarithmic scale for the X or Theta coordinate.

Log scale is not allowed if there are negative coordinates.

Log scale is not allowed for the Theta coordinate.</source>
        <translation>X 軸 の目盛を対数軸とします。

対数目盛 は 座標値に マイナスの数値が含まれる場合には利用できません。

対数目盛は偏角の座標軸には利用できません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="291" />
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="336" />
        <source>Units:</source>
        <translation>単位：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="315" />
        <source>Specifies linear scale for the Y or R coordinate</source>
        <translation>Y 座標 または 動径 R の目盛をリニアとします。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="319" />
        <source>Origin radius value:</source>
        <translation>動径の初期値：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="323" />
        <source>Specifies logarithmic scale for the Y or R coordinate

Log scale is not allowed if there are negative coordinates.</source>
        <translation>Y 座標または動径 R の目盛を対数とします。

対数目盛は座標値にマイナスの値が含まれる場合には設定できません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="330" />
        <source>Specify radius value at origin.

Normally the radius at the origin is 0, but a nonzero value may be applied in other cases (like when the radial units are decibels).</source>
        <translation>動径の初期値を設定します。

通常、動径の初期値は 0 ですが、0 ではない値を与えることもできます (例えば単位がデシベル dbである場合など) 。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="353" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="360" />
        <source>Preview window that shows how current settings affect the coordinate system.</source>
        <translation>プレビュー画面に現在の設定がどのように座標系に反映されるかが表示されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="669" />
        <source>Numbers have the simplest and most general format.

Date and time values have date and/or time components.

Degrees Minutes Seconds (DDD MM SS.S) format uses two integer number for degrees and minutes, and a real number for seconds. There are 60 seconds per minute. During input, spaces must be inserted between the three numbers.</source>
        <translation>数値軸は最も基本的でまた最も一般的な形式です。

日付と時間軸は日付あるいは日付/時刻要素を示します。

度分秒 (DDD MM SS.S) 形式では 2 つの整数値で度と分を、また実数値で秒を表します。 1 分は 60 秒です。入力の際、3 つの数値のあいだを空白文字で区切ります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="702" />
        <source>Degrees (DDD.DDDDD) format uses a single real number. One complete revolution is 360 degrees.

Degrees Minutes (DDD MM.MMM) format uses one integer number for degrees, and a real number for minutes. There are 60 minutes per degree. During input, a space must be inserted between the two numbers.

Degrees Minutes Seconds (DDD MM SS.S) format uses two integer number for degrees and minutes, and a real number for seconds. There are 60 seconds per minute. During input, spaces must be inserted between the three numbers.

Gradians format uses a single real number. One complete revolution is 400 gradians.

Radians format uses a single real number. One complete revolution is 2*pi radians.

Turns format uses a single real number. One complete revolution is one turn.</source>
        <translation>度 (DDD.DDDDD) 表示形式は実数一つで角度を表現します。一回転は 360 度です。

度分 (DDD MM.MMM) 表示形式は度を一つの整数で表し、分を一つの実数で表します。 60 分が 1 度にあたります。入力するにあたっては、これら2 つの数字のあいだに空白文字が一つ入る必要があります。

度分秒 (DDD MM SS.S) 表示形式では度と分それぞれを整数で表し、秒を実数で表します。 60 秒が 1 分にあたります。入力するにあたっては、これら3 つの数字のあいだに空白文字が一つずつ入る必要があります。

グラディアン (Gradian) 表示形式は実数一つで角度を表現します。一回転は 400 グラディアンです。

ラジアン (Radian) 表示形式は 実数一つで角度を表現します。一回転は  2*pi ラジアンです。

ターン (Turn) 表示形式は 実数一つで角度を表現します。一回転は1 ターンです。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="909" />
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCoords.cpp" line="913" />
        <source>Y</source>
        <translation>Y</translation>
    </message>
</context>
<context>
    <name>DlgSettingsCurveAddRemove</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="32" />
        <source>Curve Add/Remove</source>
        <translation>カーブの追加/削除</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="69" />
        <source>Add...</source>
        <translation>追加...</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="70" />
        <source>Adds a new curve to the curve list. The curve name can be edited in the curve name list.

Every curve name must be unique</source>
        <translation>新たにカーブをリストに追加します。カーブ名はカーブ名リストで編集することもできます。

どのカーブ名も固有で重複はできません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="76" />
        <source>Remove</source>
        <translation>削除</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="77" />
        <source>Removes the currently selected curve from the curve list.

There must always be at least one curve</source>
        <translation>カーブ名リストから選択されたカーブを削除します。

常に最低一つのカーブがリストにあるようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="89" />
        <source>Curve Names:</source>
        <translation>カーブ名：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="94" />
        <source>List of the curves belonging to this document.

Click on a curve name to edit it. Each curve name must be unique.

Reorder curves by dragging them around.</source>
        <translation>このドキュメントに含まれているカーブ名のリストです。

編集するにはカーブ名をクリックしてください。どのカーブ名も一意でなければなりません。

ドラッグすることでカーブ名の順序を変更することも可能です。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="121" />
        <source>Save As Default</source>
        <translation>デフォルトとして設定</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="122" />
        <source>Save the curve names for use as defaults for future graph curves.</source>
        <translation>カーブ名を今後グラフ カーブを作成する際のデフォルトとして設定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="126" />
        <source>Reset Default</source>
        <translation>デフォルト設定のリセット</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="127" />
        <source>Reset the defaults for future graph curves to the original settings.</source>
        <translation>グラフ カーブのデフォルトを現在の設定からオリジナルの設定にリセットします。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="506" />
        <source>Removing this curve will also remove</source>
        <translation>このカーブを削除すると、同時にポイントも削除されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="508" />
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="513" />
        <source>points. Continue?</source>
        <translation>続けますか？</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="511" />
        <source>Removing these curves will also remove</source>
        <translation>これらのカーブを削除すると、ポイントを含めてカーブが削除されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveAddRemove.cpp" line="517" />
        <source>Curves With Points</source>
        <translation>　</translation>
    </message>
</context>
<context>
    <name>DlgSettingsCurveProperties</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="61" />
        <source>Curve Properties</source>
        <translation>カーブのプロパティ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="88" />
        <source>Curve Name:</source>
        <translation>カーブ名：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="92" />
        <source>Name of the curve that is currently selected for editing</source>
        <translation>現在編集対象として選択されているカーブの名前</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="102" />
        <source>Line</source>
        <translation>ライン</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="108" />
        <source>Width:</source>
        <translation>線幅：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="112" />
        <source>Select a width for the lines drawn between points.

This applies only to graph curves. No lines are ever drawn between axis points.</source>
        <translation>ポイント間に描画されるラインの線幅を選択します。

この変更はグラフ カーブにのみ適用されます。座標軸の基準となる点のあいだにラインが描画されることはありません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="118" />
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="203" />
        <source>Color:</source>
        <translation>色：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="122" />
        <source>Select a color for the lines drawn between points.

This applies only to graph curves. No lines are ever drawn between axis points.</source>
        <translation>ポイント間に描画されるラインの色を選択します。

この変更はグラフ カーブにのみ適用されます。座標軸の基準となる点のあいだにラインが描画されることはありません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="128" />
        <source>Connect as:</source>
        <translation>ラインとポイントの接続</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="136" />
        <source>Select rule for connecting points with lines.

If the curve is connected as a single-valued function then the points are ordered by increasing value of the independent variable.

If the curve is connected as a closed contour, then the points are ordered by age, except for points placed along an existing line. Any point placed on top of any existing line is inserted between the two endpoints of that line - as if its age was between the ages of the two endpoints.

Lines are drawn between successively ordered points.

Straight curves are drawn with straight lines between successive points. Smooth curves are drawn with smooth lines between successive points.

This applies only to graph curves. No lines are ever drawn between axis points.</source>
        <translation>ポイントとラインを接続するために使うルール設定を選択します。

もし カーブ が単変数関数となるのであれば、これらの ポイント は 単純に増減する独立変数に従い並べられます。

もし カーブ が閉じたコンター（等高線）であれば、これらのポイントはすでに存在するコンター上に位置するものを除き age に従い並べられます。既存の ライン 上に位置するポイントはすべて、そのラインにおける端点のあいだに内挿されますーあたかもその age が、この二つの端点の age の間の値を持っているかのように。

ライン は連続して並べられたポイントのあいだに描かれます。

直線の カーブ は連続したポイント間に直線を描きます。曲線は 連続したポイント間を曲線で結びます。
これらのルールはグラフのカーブにのみ適用されます。座標軸の基準点の間にラインが描かれることはありません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="156" />
        <source>Point</source>
        <translation>ポイント</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="162" />
        <source>Shape:</source>
        <translation>形状：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="166" />
        <source>Select a shape for the points</source>
        <translation>ポイントの形状を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="182" />
        <source>Radius:</source>
        <translation>半径：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="186" />
        <source>Select a radius, in pixels, for the points</source>
        <translation>ポイントの半径をピクセル数で指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="191" />
        <source>Line width:</source>
        <translation>ラインの線幅：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="195" />
        <source>Select a line width, in pixels, for the points.

A larger width results in a thicker line, with the exception of a value of zero which always results in a line that is one pixel wide (which is easy to see even when zoomed far out)</source>
        <translation>ポイントを描画する線幅をピクセル数で指定します。

線幅に大きな数字を指定すると線は太くなりますが、ゼロを指定した場合には常に1 ピクセルとなります。(これはかなり縮小した場合にも見ることができるので便利です)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="207" />
        <source>Select a color for the line used to draw the point shapes</source>
        <translation>ポイントを描画する線の色を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="218" />
        <source>Save the visible curve settings for use as future defaults, according to the curve name selection.

If the visible settings are for the axes curve, then they will be used for future axes curves, until new settings are saved as the defaults.

If the visible settings are for the Nth graph curve in the curve list, then they will be used for future graph curves that are also the Nth graph curve in their curve list, until new settings are saved as the defaults.</source>
        <translation>カーブの見た目に関する設定を保存し、将来カーブ名を選択することで呼び出すことのできるデフォルトの設定とします。

ここで座標軸の基準となる点の見た目に関する設定を変更した場合には、新たな設定がデフォルトとして設定され直すまでは、これらが引き続きデフォルトとして利用されます。

もしカーブの見た目に関する設定がカーブ リストでのN番目のグラフ カーブに対して変更された場合、以降のグラフ カーブでも、カーブ リストでN番目にリストされたカーブに対するデフォルトとなります。これは新たな設定がデフォルトとして保存されるまで有効です。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="232" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsCurveProperties.cpp" line="239" />
        <source>Preview window that shows how current settings affect the points and line of the selected curve.

The X coordinate is in the horizontal direction, and the Y coordinate is in the vertical direction. A function can have only one Y value, at most, for any X value, but a relation can have multiple Y values for one X value.</source>
        <translation>プレビュー画面では現在の設定が選択されたカーブのポイントとラインにどのように影響するかを見ることができます。

X 座標は水平方向を、また Y 座標は垂直方向を表しています。 関数は一つのXの値に対しては最大で 一つしか Y の値を持てませんが、リレーションは一つの Xの値に対して複数の Y の値を持つことができます。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsDigitizeCurve</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="41" />
        <source>Digitize Curve</source>
        <translation>カーブのデジタイズ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="65" />
        <source>Cursor</source>
        <translation>カーソル</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="73" />
        <source>Type:</source>
        <translation>種類：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="76" />
        <source>Standard cross</source>
        <translation>標準設定（十字）</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="77" />
        <source>Selects the standard cross cursor</source>
        <translation>標準設定の十字カーソルを選択します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="81" />
        <source>Custom cross</source>
        <translation>カスタム（十字）</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="82" />
        <source>Selects a custom cursor based on the settings selected below</source>
        <translation>下に表示されるカスタム設定を利用して十字を表示します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="86" />
        <source>Size (pixels):</source>
        <translation>サイズ (ピクセル)：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="95" />
        <source>Horizontal and vertical size of the cursor in pixels</source>
        <translation>カーソルの水平・垂直方向のサイズ（ピクセル）</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="99" />
        <source>Inner radius (pixels):</source>
        <translation>内径 (ピクセル)：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="104" />
        <source>Radius of circle at the center of the cursor that will remain empty</source>
        <translation>円形カーソルの半径（カーソルの内側は空白となります）</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="108" />
        <source>Line width (pixels):</source>
        <translation>線幅 (ピクセル)：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="113" />
        <source>Width of each arm of the cross of the cursor</source>
        <translation>カーソル十字の各腕木部分の幅</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="127" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsDigitizeCurve.cpp" line="139" />
        <source>Preview window showing the currently selected cursor.

Drag the cursor over this area to see the effects of the current settings on the cursor shape.</source>
        <translation>プレビュー画面 には現在選択中のカーソルが表示されています。

このエリアに カーソル をドラッグして設定が カーソル の形状にどのように反映されるかを確認することができます。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsExportFormat</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="55" />
        <source>Export Format</source>
        <translation>エクスポート するファイルのフォーマット</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="79" />
        <source>Included</source>
        <translation>カーブリストを含む</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="82" />
        <source>Not included</source>
        <translation>カーブリストを含まない</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="87" />
        <source>List of curves to be included in the exported file.

The order of the curves here does not affect the order in the exported file. That order is determined by the Curves settings.</source>
        <translation>エクスポート された ファイルに、カーブリストを含めます。

エクスポート ファイルでのカーブの順番は、カーブリストでの順番に影響されません。この順番は カーブ設定 画面にて指定されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="96" />
        <source>List of curves to be excluded from the exported file</source>
        <translation>エクスポートされたファイルには、カーブ リストが含まれません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="101" />
        <source>&lt;&lt;Include</source>
        <translation>＜＜ 含める</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="103" />
        <source>Move the currently selected curve(s) from the excluded list</source>
        <translation>選択された カーブ を、除外対象 (リスト) から 移動 します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="107" />
        <source>Exclude&gt;&gt;</source>
        <translation>除外＞＞</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="109" />
        <source>Move the currently selected curve(s) from the included list</source>
        <translation>選択された カーブ を、除外対象 (リスト) に移動します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="120" />
        <source>Delimiters</source>
        <translation>区切り文字</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="127" />
        <source>Exported file will have commas between adjacent values, unless overridden by tabs in TSV files.</source>
        <translation>エクスポートされたファイルは隣り合う数値間をコンマで区切られます。但しTSVファイルとしてタブ区切りで置き換えられる場合を除きます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="132" />
        <source>Exported file will have spaces between adjacent values, unless overridden by commas in CSV files, or tabs in TSV files.</source>
        <translation>エクスポートされたファイルは隣り合う数値間を空白文字で区切られます。但しCSVファイルとしてカンマ区切りとなる場合、あるいはTSVファイルとしてタブ区切りで置き換えられる場合を除きます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="138" />
        <source>Exported file will have tabs between adjacent values, unless overridden by commas in CSV files.</source>
        <translation>エクスポートされたファイルは隣り合う数値間をタブで区切られます。但しCSVファイルとしてカンマ区切りで置き換えられる場合を除きます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="143" />
        <source>Exported file will have semicolons between adjacent values, unless overridden by commas in CSV files.</source>
        <translation>エクスポートされたファイルは隣り合う数値間をセミコロンで区切られます。但しCSVファイルとしてカンマ区切りで置き換えられる場合を除きます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="147" />
        <source>Override in CSV/TSV files</source>
        <translation>CSV/TSV 形式の指定</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="148" />
        <source>Comma-separated value (CSV) files and tab-separated value (TSV) files will use commas and tabs respectively, unless this setting is selected. Selecting this setting will apply the delimiter setting to every file.</source>
        <translation>ここでCSVあるいはTSVを指定することで直接出力ファイル形式を設定できます。特に指定しなければファイル中でのコンマ区切り(CSV)あるいはタブ区切り(TSV)が尊重されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="159" />
        <source>Layout</source>
        <translation>エクスポート ファイルのレイアウト：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="165" />
        <source>All curves on each line</source>
        <translation>一行に全カーブ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="166" />
        <source>Exported file will have, on each line, an X value, the Y value for the first curve, the Y value for the second curve,...</source>
        <translation>エクスポートされたファイルの各行には、X 値、最初の カーブ の Y 値、次の カーブ のY値、の順にデータが並びます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="171" />
        <source>One curve on each line</source>
        <translation>一行に 1 つの カーブ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="172" />
        <source>Exported file will have all the points for the first curve, with one X-Y pair on each line, then the points for the second curve,...</source>
        <translation>エクスポートされたファイルは、まず 1 つめの カーブ の全ポイントを一組の X - Y のペアとして各行に記述し、引き続き 2 つ目以降の カーブ を順次記述していきます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="182" />
        <source>Function Points Selection</source>
        <translation>近似式で補間する際に使用する X 値の読み取り方法の選択</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="196" />
        <source>Interpolate Ys at Xs from all curves</source>
        <translation>全 カーブ の X について Y を 補間 </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="197" />
        <source>Exported file will have values at every unique X value from every curve. Y values will be linearly interpolated if necessary</source>
        <translation>エクスポートされたファイルには、全てのカーブから 重複しない X を全て用います。Y の値は必要に応じて 補間 されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="202" />
        <source>Interpolate Ys at Xs from first curve</source>
        <translation>最初の カーブ の  X について Y を 補間</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="203" />
        <source>Exported file will have values at every unique X value from the first curve. Y values will be linearly interpolated if necessary</source>
        <translation>エクスポートされたファイルには、最初の カーブ から X を用います。Y の値は必要に応じて 補間 されます</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="208" />
        <source>Interpolate Ys at evenly spaced X values.</source>
        <translation>等間隔の X について Y を 補間 </translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="209" />
        <source>Exported file will have values at evenly spaced X values, separated by the interval selected below.</source>
        <translation>エクスポートされたファイルには、等間隔に区切られた X が用いられます。インターバルは以下にて設定できます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="213" />
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="350" />
        <source>Interval:</source>
        <translation>インターバル：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="221" />
        <source>Interval, in the units of X, between successive points in the X direction.

If the scale is linear, then this interval is added to successive X values. If the scale is logarithmic, then this interval is multiplied to successive X values.

The X values will be automatically aligned along simple numbers. If the first and/or last points are not along the aligned X values, then one or two additional points are added as necessary.</source>
        <translation>インターバルは X 方向に連続するポイント間の間隔です。

リニア スケール であれば、このインターバルを X 値に加えて次の X 値が得られます。 対数 スケールであれば、このインターバルを乗じることで次の X 値が得られます。

X 値は できるだけシンプルな数値の並びになるように設定されます。もし最初のポイントあるいは最後のポイントが数値の並びに沿わない場合、1 あるいは 2 つのポイントが必要に応じて追加されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="231" />
        <source>Units for spacing interval.

Pixel units are preferred when the spacing is to be independent of the X scale. The spacing will be consistent across the graph, even if the X scale is logarithmic.

Graph units are preferred when the spacing is to depend on the X scale.</source>
        <translation>インターバルの単位

インターバル間隔をX 軸の目盛単位とは別に定めるときにはピクセル単位が有用です。その場合、例え X 軸が対数目盛であっても、そのグラフ内ではインターバル間隔に整合性が保たれます。

なおインターバル間隔を X の目盛単位に合わせるには、グラフの目盛単位を利用します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="243" />
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="376" />
        <source>Raw Xs and Ys</source>
        <translation>X および Y の原データ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="244" />
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="377" />
        <source>Exported file will have only original X and Y values</source>
        <translation>エクスポートされたファイルは元のXとYの値だけを含みます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="255" />
        <source>Header</source>
        <translation>ヘッダー情報</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="265" />
        <source>Exported file will have no header line</source>
        <translation>エクスポートされたファイルはヘッダー行を含みません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="270" />
        <source>Exported file will have simple header line</source>
        <translation>エクスポートされたファイルは簡易なヘッダー行を含みます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="275" />
        <source>Exported file will have gnuplot header line</source>
        <translation>エクスポートされたファイルはgnuplotに対応するヘッダー行を含みます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="287" />
        <source>Save As Default</source>
        <translation>デフォルトとして設定</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="288" />
        <source>Save the settings for use as future defaults.</source>
        <translation>設定情報を以後のデフォルトとして保存します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="297" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="313" />
        <source>Preview window shows how current settings affect the exported file.

Functions (shown here in blue) are output first, followed by relations (shown here in green) if any exist.</source>
        <translation>プレビュー 画面では、設定により エクスポート された ファイル がどのようになるかを見ることができます。

(青色で表示された) 近似式による補間結果がまず出力され、またポイント 間を順に接続して得られたライン (緑色) による補間結果があれば、これも続いて出力されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="329" />
        <source>Relation Points Selection</source>
        <translation>ポイント 間の接続線からの X 値の読み取り方法の選択</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="343" />
        <source>Interpolate Xs and Ys at evenly spaced intervals.</source>
        <translation>XとYについて、それぞれ等間隔に 補間 して値を出力します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="344" />
        <source>Exported file will have points evenly spaced along each relation, separated by the interval selected below. If the last interval does not end at the last point, then a shorter last interval is added that ends on the last point.</source>
        <translation>エクスポートされたファイルは、それぞれの リレーション に沿って、等間隔に ポイント を含みます。もし最後のインターバルが最後の点で丁度終わらなければ、最後のインターバル間隔は最後の点と合致するように少し短く調整されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="358" />
        <source>Interval between successive points when exporting at evenly spaced (X,Y) coordinates.</source>
        <translation>等間隔の座標でエクスポートする際の、連続したポイント間の間隔</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="364" />
        <source>Units for spacing interval.

Pixel units are preferred when the spacing is to be independent of the X and Y scales. The spacing will be consistent across the graph, even if a scale is logarithmic or the X and Y scales are different.

Graph units are usually preferred when the X and Y scales are identical.</source>
        <translation>インターバル間隔 の単位

X 軸・ Y 軸の目盛とは別に間隔を設定したい場合にはピクセル単位 がおすすめです。 もし目盛が対数であっても、またX 軸・ Y 軸の目盛が互いに異なっていても、グラフ内では目盛の一貫性が保てるためです。

グラフの目盛単位は通常X 軸・ Y 軸の目盛が同一である場合に利用が勧められます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="420" />
        <source>Functions</source>
        <translation>座標取得機能</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="422" />
        <source>Functions Tab

Controls for specifying the format of functions during export</source>
        <translation>座標取得機能タブ

座標を取得してエクスポートする際に利用するオプションを選択します。X軸について等間隔とする場合にはそのインターバルも指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="428" />
        <source>Relations</source>
        <translation>リレーション機能</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="430" />
        <source>Relations Tab

Controls for specifying the format of relations during export</source>
        <translation>リレーション機能タブ

座標を取得してエクスポートする際に利用するオプションを選択し、等間隔とする場合にはインターバルを指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="451" />
        <source>X Label:</source>
        <translation>X軸ラベル</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="453" />
        <source>Theta Label:</source>
        <translation>偏角ラベル</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="459" />
        <source>Label in the header for x values</source>
        <translation>ヘッダー情報に X軸 をラベルとして含める。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="461" />
        <source>Label in the header for theta values</source>
        <translation>ヘッダー情報に 偏角 をラベルとして含める。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsExportFormat.cpp" line="1117" />
        <source>Preview is unavailable until axis points are defined.</source>
        <translation>プレビュー 画面は座標軸の基準となる ポイント が設定されるまでは表示されません。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsGeneral</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="25" />
        <source>General</source>
        <translation>一般設定</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="47" />
        <source>Effective cursor size (pixels):</source>
        <translation>実効 カーソル サイズ (ピクセル単位)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="52" />
        <source>Effective Cursor Size

This is the effective width and height of the cursor when clicking on a pixel that is not part of the background.

This parameter is used in the Color Picker and Point Match modes</source>
        <translation>実効 カーソル サイズ

この ピクセル単位 で指定された幅および高さの範囲が、クリックした際に読み取りの対象となる（バックグラウンドではない）ピクセルとして判別されます。

カラーピッカー モードと ポイントマッチ モード で利用されるパラメーターです。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="59" />
        <source>Extra precision (digits):</source>
        <translation>追加精度 (桁)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="64" />
        <source>Extra Digits of Precision

This is the number of additional digits of precision appended after the significant digits determined by the digitization accuracy at that point. The digitization accuracy at any point equals the change in graph coordinates from moving one pixel in each direction. Appending extra digits does not improve the accuracy of the numbers. More information can be found in discussions of accuracy versus precision.

This parameter is used on the coordinates in the Status Bar and during Export</source>
        <translation>精度桁の追加

ポイントをデジタイズして得られた有効精度桁に桁を追加します。各ポイントでのデジタイズの精度はそれぞれの軸方向への 1 ピクセル 分の移動量をグラフ座標の単位で表したものに相当します。桁数を追加することは数値の精度自体を向上させるものではありません。 正確さと精度の違いについては別途説明していますので参照してください。

この パラメーター は ステータスバー での 座標表示と エクスポート に際して使われます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="79" />
        <source>Save As Default</source>
        <translation>デフォルトとして設定</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGeneral.cpp" line="80" />
        <source>Save the settings for use as future defaults, according to the curve name selection.</source>
        <translation>以降のデフォルトとして設定し、カーブ名を選ぶことで呼び出します。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsGridDisplay</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="31" />
        <source>Grid Display</source>
        <translation>グリッドの表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="65" />
        <source>Color:</source>
        <translation>色：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="69" />
        <source>Select a color for the lines</source>
        <translation>グリッドの罫線を表示する色を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="91" />
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="167" />
        <source>Disable:</source>
        <translation>除外対象：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="95" />
        <source>Disabled value.

The X grid lines are specified using only three values at a time. For flexibility, four values are offered so you must chose which value is disabled. Once disabled, that value is simply updated as the other values change</source>
        <translation>除外対象

グリッドの X 枠線を設定するために 4 つのパラメーターを調整可能ですが、一度に変更できるのは、そのうち3 つの要素です。 そのため、まず変更しないパラメーターを除外対象として指定してから調整を始めてください。その際、除外されたパラメーターの値は他の 3 つのパラメーターが変更されるのに伴い自動的に更新されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="110" />
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="186" />
        <source>Count:</source>
        <translation>本数：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="114" />
        <source>Number of X grid lines.

The number of X grid lines must be entered as an integer greater than zero</source>
        <translation>X 枠線の本数

X 枠線の本数を 1 以上の整数で指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="123" />
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="199" />
        <source>Start:</source>
        <translation>開始位置：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="127" />
        <source>Value of the first X grid line.

The start value cannot be greater than the stop value</source>
        <translation>X 枠線の開始位置

X 枠線を開始する位置です。この値は終了位置の値よりも大きくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="134" />
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="210" />
        <source>Step:</source>
        <translation>ステップ間隔：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="138" />
        <source>Difference in value between two successive X grid lines.

The step value must be greater than zero</source>
        <translation>左右に隣り合う 2 本の X 枠線の値の差分に相当します。

ゼロよりも大きな値を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="145" />
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="221" />
        <source>Stop:</source>
        <translation>終了位置：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="149" />
        <source>Value of the last X grid line.

The stop value cannot be less than the start value</source>
        <translation>X 枠線の終了位置

X 枠線を終了する位置です。この値は開始位置の値よりも小さくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="171" />
        <source>Disabled value.

The Y grid lines are specified using only three values at a time. For flexibility, four values are offered so you must chose which value is disabled. Once disabled, that value is simply updated as the other values change</source>
        <translation>除外対象：

グリッドの Y 枠線を設定するために 4 つのパラメーターを調整可能ですが、一度に変更できるのは、そのうち3 つの要素です。 そのため、まず変更しないパラメーターを除外対象として指定してから調整を始めてください。その際、除外されたパラメーターの値は他の 3 つのパラメーターが変更されるのに伴い自動的に更新されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="190" />
        <source>Number of Y grid lines.

The number of Y grid lines must be entered as an integer greater than zero</source>
        <translation>Y 枠線の本数

Y 枠線の本数を 1 以上の整数で指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="203" />
        <source>Value of the first Y grid line.

The start value cannot be greater than the stop value</source>
        <translation>Y 枠線の開始位置

Y 枠線を開始する位置です。この値は終了位置の値よりも大きくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="214" />
        <source>Difference in value between two successive Y grid lines.

The step value must be greater than zero</source>
        <translation>上下に隣り合う 2 本の Y 枠線の値の差分に相当します。

ゼロよりも大きな値を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="225" />
        <source>Value of the last Y grid line.

The stop value cannot be less than the start value</source>
        <translation>Y 枠線の終了位置

Y 枠線を終了する位置です。この値は開始位置の値よりも小さくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="241" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="248" />
        <source>Preview window that shows how current settings affect grid display</source>
        <translation>プレビュー画面 では、現在の設定がどのように枠線の表示に影響するかを見ることができます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="309" />
        <source>X Grid Lines</source>
        <translation>X 枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="311" />
        <source>Grid Lines</source>
        <translation>グリッド 線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="315" />
        <source>Y Grid Lines</source>
        <translation>Y 枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="317" />
        <source>Radius Grid Lines</source>
        <translation>動径枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridDisplay.cpp" line="575" />
        <source>Grid line count exceeds limit set by Settings / Main Window.</source>
        <translation>グリッド数が設定/メインウィンドウで設定した制限を超えています。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsGridRemoval</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="33" />
        <source>Grid Removal</source>
        <translation>枠線近傍の消去</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="60" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="67" />
        <source>Preview window that shows how current settings affect grid removal</source>
        <translation>プレビュー画面で現在の設定が枠線近傍のピクセル消去にどのように反映されるかを見ることができます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="78" />
        <source>Remove pixels close to defined grid lines</source>
        <translation>設定した枠線近傍のピクセルを消去</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="79" />
        <source>Check this box to have pixels close to regularly spaced gridlines removed.

This option is only available when the axis points have all been defined.</source>
        <translation>このチェックボックス に チェック を入れると、等間隔のグリッドとして設定した枠線に近いピクセルを消去して視認性を上げることができます。

このオプションは、座標軸の基準となる点をすべて設定すると利用できるようになります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="84" />
        <source>Close distance (pixels):</source>
        <translation>枠線からの距離 (ピクセル)：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="88" />
        <source>Set closeness distance in pixels.

Pixels that are closer to the regularly spaced gridlines, than this distance, will be removed.

This value cannot be negative. A zero value disables this feature. Decimal values are allowed</source>
        <translation>消去対象に含める距離を枠線からのピクセル数で指定します。

等間隔のグリッドとして設定された枠線に指定したピクセル数よりも近い位置にあるピクセルは消去されます。

マイナスの値を与えることはできません。また少数点以下の数値も使えますが、ゼロを指定するとこの機能は無効化されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="105" />
        <source>X Grid Lines</source>
        <translation>X 枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="107" />
        <source>Grid Lines</source>
        <translation>グリッド 線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="115" />
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="193" />
        <source>Disable:</source>
        <translation>除外対象：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="119" />
        <source>Disabled value.

The X grid lines are specified using only three values at a time. For flexibility, four values are offered so you must chose which value is disabled. Once disabled, that value is simply updated as the other values change</source>
        <translation>除外対象

グリッドの X 枠線を設定するために 4 つのパラメーターを調整可能ですが、一度に変更できるのは、そのうち3 つの要素です。 そのため、まず変更しないパラメーターを除外対象として指定してから調整を始めてください。その際、除外されたパラメーターの値は他の 3 つのパラメーターが変更されるのに伴い自動的に更新されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="134" />
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="212" />
        <source>Count:</source>
        <translation>本数：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="138" />
        <source>Number of X grid lines.

The number of X grid lines must be entered as an integer greater than zero</source>
        <translation>X 枠線の本数

X 枠線の本数を 1 以上の整数で指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="145" />
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="223" />
        <source>Start:</source>
        <translation>開始位置：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="149" />
        <source>Value of the first X grid line.

The start value cannot be greater than the stop value</source>
        <translation>X 枠線の開始位置

X 枠線を開始する位置です。この値は終了位置の値よりも大きくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="156" />
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="234" />
        <source>Step:</source>
        <translation>ステップ間隔：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="160" />
        <source>Difference in value between two successive X grid lines.

The step value must be greater than zero</source>
        <translation>左右に隣り合う 2 本の X 枠線の値の差分に相当します。

ゼロよりも大きな値を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="167" />
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="245" />
        <source>Stop:</source>
        <translation>終了位置：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="171" />
        <source>Value of the last X grid line.

The stop value cannot be less than the start value</source>
        <translation>X 枠線の終了位置

X 枠線を終了する位置です。この値は開始位置の値よりも小さくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="183" />
        <source>Y Grid Lines</source>
        <translation>Y 枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="185" />
        <source>R Grid Lines</source>
        <translation>R 枠線</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="197" />
        <source>Disabled value.

The Y grid lines are specified using only three values at a time. For flexibility, four values are offered so you must chose which value is disabled. Once disabled, that value is simply updated as the other values change</source>
        <translation>除外対象：

グリッドの Y 枠線を設定するために 4 つのパラメーターを調整可能ですが、一度に変更できるのは、そのうち3 つの要素です。 そのため、まず変更しないパラメーターを除外対象として指定してから調整を始めてください。その際、除外されたパラメーターの値は他の 3 つのパラメーターが変更されるのに伴い自動的に更新されます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="216" />
        <source>Number of Y grid lines.

The number of Y grid lines must be entered as an integer greater than zero</source>
        <translation>Y 枠線の本数

Y 枠線の本数を 1 以上の整数で指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="227" />
        <source>Value of the first Y grid line.

The start value cannot be greater than the stop value</source>
        <translation>Y 枠線の開始位置

Y 枠線を開始する位置です。この値は終了位置の値よりも大きくならないようにしてください。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="238" />
        <source>Difference in value between two successive Y grid lines.

The step value must be greater than zero</source>
        <translation>上下に隣り合う 2 本の Y 枠線の値の差分に相当します。

ゼロよりも大きな値を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsGridRemoval.cpp" line="249" />
        <source>Value of the last Y grid line.

The stop value cannot be less than the start value</source>
        <translation>Y 枠線の終了位置

Y 枠線を終了する位置です。この値は開始位置の値よりも小さくならないようにしてください。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsMainWindow</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="34" />
        <source>Main Window</source>
        <translation>メイン画面</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="59" />
        <source>Initial zoom:</source>
        <translation>初期画面の倍率：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="74" />
        <source>Initial Zoom

Select the initial zoom factor when a new document is loaded. Either the previous zoom can be kept, or the specified zoom can be applied.</source>
        <translation>初期倍率

新たにドキュメントを開いたときに画面に表示される倍率を設定します。前回閉じたときの倍率を維持することもできますし、また倍率を指定して開くこともできます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="80" />
        <source>Zoom control:</source>
        <translation>倍率の変更：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="84" />
        <source>Menu only</source>
        <translation>メニューのみ</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="85" />
        <source>Menu and mouse wheel</source>
        <translation>メニューおよびマウス ホィールを使用</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="86" />
        <source>Menu and +/- keys</source>
        <translation>メニューおよび +/- キーを使用</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="87" />
        <source>Menu, mouse wheel and +/- keys</source>
        <translation>メニュー、マウス ホィール、あるいは +/- キーを使用</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="88" />
        <source>Zoom Control

Select which inputs are used to zoom in and out.</source>
        <translation>倍率のコントロール

倍率の拡大・縮小にどの入力方法を使うかを選べます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="93" />
        <source>Locale:</source>
        <translation>ロケール</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="98" />
        <source>Locale

Select the locale that will be used in numbers (immediately), and the language in the user interface (after restart).

The locale determines how numbers are formatted. Specifically, either commas or periods will be used as group delimiters in each number entered by the user, displayed in the user interface, or exported to a file.</source>
        <translation>ロケール

ロケール を選択します。ロケール を変更すると数値の表示形式はすぐに反映されますが、ユーザーインターフェースの言語は再起動後に反映されることになります。

ロケール は数値の表現形式を決定付けますが、特に コンマ とピリオド はユーザーインターフェースでの表示に加えて出力ファイルでの取り扱いに影響します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="118" />
        <source>Import cropping:</source>
        <translation>画像をトリミングしてインポート</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="122" />
        <source>Import Cropping

Enables or disables cropping of the imported image when importing. Cropping the image is useful for removing unimportant information around a graph, but less useful when the graph already fills the entire image.

This setting only has an effect when Engauge has been built with support for pdf files.</source>
        <translation>画像をトリミングしてインポート

画像を インポート する際に周囲をトリミングするかどうかを指定します。 画像のトリミングは画像周辺の不要な部分を除去するのに有用ですが、もしグラフが画像いっぱいに描画されているのであればあまり意味はありません。

この設定は、Engaugeがpdfファイルをサポートするように構築されている場合にのみ有効です。
</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="135" />
        <source>Import PDF resolution (dots per inch):</source>
        <translation>PDF インポート の解像度 (dpi)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="139" />
        <source>Import PDF Resolution

Imported Portable Document Format (PDF) files will be converted to this pixel resolution in dots per inch (DPI), where each pixel is one dot. A higher value increases the picture resolution and may also improve numeric digitizing accuracy. However, a very high value can make the image so large that Engauge will slow down.</source>
        <translation>PDF インポート の解像度

Portable Document Format (PDF) ファイルをインポートすると、ここで指定した解像度  (dots per inch: DPI)に変換されます。ここでのドットはピクセルに相当します。 値を大きくすると解像度が上がり、デジタイズ精度がよくなる可能性があります。一方で、あまり大きな値を与えて画像ファイルサイズが大きいと Engauge の動きが遅くなります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="154" />
        <source>Maximum grid lines:</source>
        <translation>枠線の最大数</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="159" />
        <source>Maximum Grid Lines

Maximum number of grid lines to be processed. This limit is applied when the step value is too small for the start and stop values, which would result in too many grid lines visually and possibly extremely long processing time (since each grid line would have to be processed)</source>
        <translation>枠線の最大数

ここで作成できる枠線の最大本数を指定します。この上限値を設定することで、枠線を生成する際にその範囲に比べてインターバル間隔が小さすぎるなど、枠線が多すぎて見分けがつかなくなったり、処理に時間がかかりすぎたりすることを防ぐことができます。 (各枠線の処理にある程度の時間を要します)。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="166" />
        <source>Highlight opacity:</source>
        <translation>ハイライト時の透明度</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="172" />
        <source>Highlight Opacity

Opacity to be applied when the cursor is over a curve or axis point in Select mode. The change in appearance shows when the point can be selected.</source>
        <translation>ハイライト時の透明度

選択モードで カーブ あるいは座標軸の基準点にマウスを重ねると、透明度の変化でハイライトしています。この見た目の変化でポイントがいつ選択されたかなどを知ることができます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="178" />
        <source>Recent file list:</source>
        <translation>最近利用したファイルのリスト</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="181" />
        <source>Clear</source>
        <translation>クリア</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="183" />
        <source>Recent File List Clear

Clear the recent file list in the File menu.</source>
        <translation>最近利用したファイルリストのクリア

ファイル メニューに表示される 最近利用したファイルリストをクリアすることができます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="189" />
        <source>Include title bar path:</source>
        <translation>タイトルバーにファイルへのパスを含める</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="194" />
        <source>Title Bar Filename

Includes or excludes the path and file extension from the filename in the title bar.</source>
        <translation>タイトル バー のファイル名表示

タイトル バーにはファイル名が表示されますが、同時にファイルへのパスや拡張子を表示するか非表示とするかを選択できます。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="199" />
        <source>Allow small dialogs:</source>
        <translation>設定画面を小さく</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="204" />
        <source>Allow Small Dialogs

Allows settings dialogs to be made very small so they fit on small computer screens.</source>
        <translation>設定画面を小さく

設定画面を可能な限り小さくして、小型のコンピューターの画面で扱いやすくします。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="209" />
        <source>Allow drag and drop export:</source>
        <translation>ドラッグ アンド ドロップ でのエクスポートを許可</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsMainWindow.cpp" line="214" />
        <source>Allow Drag and Drop Export

Allows drag and drop export from the Curve Fitting Window and Geometry Window tables.

When drag and drop is disabled, a rectangular set of table cells can be selected using click and drag. When drag and drop is enabled, a rectangular set of table cells can be selected using Click then Shift+Click, since click and drag starts the drag operation.</source>
        <translation>ドラッグ アンド ドロップ でのエクスポートを許可

カーブ フィッティング 画面 や ジオメトリ 画面からのドラッグ アンド ドロップ でのエクスポートを可能にします。

ドラッグ アンド ドロップ でのエクスポートを許可しない状態であれば、クリック アンド ドラッグ でセルを長方形のテーブル状に選択することができます。一方、ドラッグ アンド ドロップ でのエクスポートを許可しているときには、クリック したあとに シフトボタンを押しながらクリックすることでセルを選択状態にします。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsPointMatch</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="30" />
        <source>Point Match</source>
        <translation>ポイント マッチング</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="83" />
        <source>Maximum point size (pixels):</source>
        <translation>ポイント サイズ の上限 (ピクセル数)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="87" />
        <source>Select a maximum point size in pixels.

Sample match points must fit within a square box, around the cursor, having width and height equal to this maximum.

This size is also used to determine if a region of pixels that are on, in the processed image, should be ignored since that region is wider or taller than this limit.

This value has a lower limit</source>
        <translation>ポイント サイズ の上限値をピクセル数で指定します。

マッチングの対象となるポイントは、ここで指定したサイズを上限とする幅と高さを持ちカーソル範囲を囲む正方形内に収まる必要があります。

このサイズはまた、処理済み画像上に指定されたピクセル範囲がここで指定した上限値よりも大きい場合にはそれを無視するための判断にも利用されます。
この値には設定できる下限もあります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="98" />
        <source>Accepted point color:</source>
        <translation>アクセプト されたポイントの表示色</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="102" />
        <source>Select a color for matched points that are accepted</source>
        <translation>アクセプト された マッチング ポイントを示すための色を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="107" />
        <source>Rejected point color:</source>
        <translation>リジェクト された ポイント の表示色</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="111" />
        <source>Select a color for matched points that are rejected</source>
        <translation>リジェクト された マッチング ポイントを示すための色を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="116" />
        <source>Candidate point color:</source>
        <translation>候補 ポイント の表示色</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="120" />
        <source>Select a color for the point being decided upon</source>
        <translation>判断の対象となる ポイント の表示色を指定します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="135" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsPointMatch.cpp" line="142" />
        <source>Preview window shows how current settings affect point matching, and how the marked and candidate points are displayed.

The points are separated by the point separation value, and the maximum point size is shown as a box in the center</source>
        <translation>プレビュー ウィンドウには、ポイント マッチング設定またマーク済みあるいは作業対象のポイントの表示設定がどのように反映されるかを見ることができます。

これらの ポイント は 指定されたポイント 間隔に基づき表示され、またポイント サイズ の上限値は中央のボックスのサイズとして見てとることができます。</translation>
    </message>
</context>
<context>
    <name>DlgSettingsSegments</name>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="40" />
        <source>Segment Fill</source>
        <translation>セグメント フィル</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="78" />
        <source>Minimum length (points):</source>
        <translation>最短長 (ポイント)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="83" />
        <source>Select a minimum number of points in a segment.

Only segments with more points will be created.

This value should be as large as possible to reduce memory usage. This value has a lower limit</source>
        <translation>一つの線分を表すのに必要な最小のポイント数を指定します。

ここで指定した数以上のポイントを持つ線分のみが生成されます。

メモリ消費量を抑えるためには、この値はできるだけ大きくすることが望まれます。この値には設定できる下限があります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="90" />
        <source>Point separation (pixels):</source>
        <translation>ポイント 間隔 (ピクセル)</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="95" />
        <source>Select a point separation in pixels.

Successive points added to a segment will be separated by this number of pixels. If Fill Corners is enabled, then additional points will be inserted at corners so some points will be closer.

This value has a lower limit</source>
        <translation>ポイント 間隔をピクセル数で指定します。

連続したポイントが線分に与えられますが、それらのポイント間にはここでピクセル数で指定した間隔が空けられます。 ただし「 屈曲点を追加」 がオンになっている場合、屈曲の大きな位置に ポイント  が追加されるので、その周辺では ポイント 間隔 は狭くなります。

この値には下限があります。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="103" />
        <source>Fill corners:</source>
        <translation>屈曲点を追加</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="107" />
        <source>Fill corners.

In addition to the points placed at regular intervals, this option causes a point to be placed at each corner. This option can capture important information in piecewise linear graphs, but gradually curving graphs may not benefit from the additional points</source>
        <translation>屈曲点を追加

通常、ポイント は 等間隔に与えられますが、オプションとして各屈曲点にポイントを追加することができます。 このオプションをオンにすると、区分的線形グラフなどで重要なデータを維持するのに役立ちますが、比較的ゆるやかにカーブするグラフに利用しても ポイント を追加するメリットはないかも知れません。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="114" />
        <source>Line width:</source>
        <translation>ラインの線幅：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="118" />
        <source>Select a size for the lines drawn along a segment</source>
        <translation>線分に沿って描画されるラインの線幅を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="123" />
        <source>Line color:</source>
        <translation>ラインの色：</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="127" />
        <source>Select a color for the lines drawn along a segment</source>
        <translation>線分に沿って描画されるラインの色を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="142" />
        <source>Preview</source>
        <translation>プレビュー表示</translation>
    </message>
    <message>
        <location filename="../src/Dlg/DlgSettingsSegments.cpp" line="149" />
        <source>Preview window shows the shortest line that can be segment filled, and the effects of current settings on segments and points generated by segment fill</source>
        <translation>プレビュー ウィンドウには線分を追加する最短のラインが表示され、現在の設定が生成される 線分 や ポイント にどのように反映されるかを見てとることができます。</translation>
    </message>
</context>
<context>
    <name>FittingWindow</name>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="41" />
        <location filename="../src/Fitting/FittingWindow.cpp" line="42" />
        <source>Curve Fitting Window</source>
        <translation>カーブ フィッティング 画面</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="43" />
        <source>Curve Fitting Window

This window applies a curve fit to the currently selected curve.

If drag-and-drop is disabled, a rectangular set of cells may be selected by clicking and dragging. Otherwise, if drag-and-drop is enabled, a rectangular set of cells may be selected using Click then Shift+Click, since click and drag starts the dragging operation. Drag-and-drop mode is set in the Main Window settings</source>
        <translation>カーブ フィット 画面

この画面では、現在選択中の カーブ について カーブ フィット を適用することができます。

もし ドラッグ アンド ドロップ が有効になっていない場合には、クリックしてからドラッグすることでその四角形の範囲を選択状態にすることができます。逆に ドラッグ アンド ドロップ が有効な場合には、クリックしてからシフトキーを押しながら再度クリックし四角形の範囲を選択します。なおドラッグ アンド ドロップ を有効にするには メイン画面 設定を利用してください。</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="126" />
        <source>Order:</source>
        <translation>多項式の次数</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="151" />
        <source>Mean square error:</source>
        <translation>平均二乗誤差</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="156" />
        <source>Calculated mean square error statistic</source>
        <translation>平均二乗誤差の計算結果</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="159" />
        <source>Root mean square:</source>
        <translation>二乗平均平方根</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="164" />
        <source>Calculated root mean square statistic. This is calculated as the square root of the mean square error</source>
        <translation>二乗平均平方根の計算結果。（平均二乗誤差の平方根として得られます）。</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="167" />
        <source>R squared:</source>
        <translation>決定係数</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="172" />
        <source>Calculated R squared statistic</source>
        <translation>決定係数の計算結果</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="226" />
        <source>log10(Y)=</source>
        <translation>log10(Y)=</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="227" />
        <source>Y=</source>
        <translation>Y=</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="232" />
        <source>log10(X)</source>
        <translation>log10(X)</translation>
    </message>
    <message>
        <location filename="../src/Fitting/FittingWindow.cpp" line="233" />
        <source>X</source>
        <translation>X</translation>
    </message>
</context>
<context>
    <name>GeometryWindow</name>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="40" />
        <location filename="../src/Geometry/GeometryWindow.cpp" line="41" />
        <source>Geometry Window</source>
        <translation>カーブ の形状画面</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="42" />
        <source>Geometry Window

This table displays the following geometry data for the currently selected curve:

Function area = Area under the curve if it is a function

Polygon area = Area inside the curve if it is a relation. This value is only correct if none of the curve lines intersect each other

X = X coordinate of each point

Y = Y coordinate of each point

Index = Point number

Distance = Distance along the curve in forward or backward direction, in either graph units or as a percentage

If drag-and-drop is disabled, a rectangular set of cells may be selected by clicking and dragging. Otherwise, if drag-and-drop is enabled, a rectangular set of cells may be selected using Click then Shift+Click, since click and drag starts the dragging operation. Drag-and-drop mode is set in the Main Window settings</source>
        <translation>ジオメトリ 画面

この 表形式 の画面には、現在選択されている カーブ についての以下の情報が表示されます：

関数の領域面積 = カーブ が関数を表している場合、そのカーブの下にできる領域の面積

ポリゴンの面積 = カーブ がリレーションを表している場合、カーブがつくるポリゴンの内側の面積。この値は表示されているカーブが互いに交差していない場合にのみ正しい値になります。

X = 各 ポイント の X 座標

Y = 各 ポイント の Y 座標

Index = ポイント の番号

Distance = カーブに沿った 距離で、グラフ 単位あるいはパーセンテージ で表示されます。

ドラッグ アンド ドロップ 機能が無効になっているときは、マウス をクリックしドラッグすることで四角形の範囲のセルを選択することができるでしょう。逆に、ドラッグ アンド ドロップ 機能を有効にしていれば、マウスをクリックして Shift キーを押しながらクリックすることで四角形の範囲のセルを選択することになるでしょう。なおドラッグ アンド ドロップ 機能 はメイン画面の設定 で切り替えできます。</translation>
    </message>
</context>
<context>
    <name>GraphicsView</name>
    <message>
        <location filename="../src/Graphics/GraphicsView.cpp" line="54" />
        <source>Main Window

After an image file is imported, or an Engauge Document opened, an image appears in this area. Points are added to the image.

If the image is a graph with two axes and one or more curves, then three axis points must be created along those axes. Just put two axis points on one axis and a third axis point on the other axis, as far apart as possible for higher accuracy. Then curve points can be added along the curves.

If the image is a map with a scale to define length, then two axis points must be created at either end of the scale. Then curve points can be added.

Zooming the image in or out is performed using any of several methods:
1) rotating the mouse wheel when the cursor is outside of the image
2) pressing the minus or plus keys
3) selecting a new zoom setting from the View/Zoom menu</source>
        <translation>メイン画面

画像をインポートした、あるいは  Engauge ドキュメントを開いた時点で、この画面には画像が1枚表示されているはずです。この画面上で ポイント を追加していくことになります。

もし画像が 2つの軸と1つ以上のカーブからなるグラフ であれば、まず座標軸の基準となる3つの点を指定する必要があります。まずは一方の軸上に2点を、そして3つめの点を他方の軸上に打ってください。これらの点が互いにできるだけ離れているとデジタイズの精度が向上します。 それから カーブ のポイント を カーブ に沿って追加していくことが可能になります。

もし 画像が距離を示す スケール バー を含む地図であれば、この スケール バー の両端を軸の基準点とすることになります。その後 カーブ のポイントを追加していきます。

画像を拡大縮小するにはいくつかの方法があります。
1) マウスカーソルが画像範囲の外にあるときには、マウス のホイールボタンの回転
2) キーボードのマイナスボタンとプラスボタン
3)  ビュー/ズーム メニュー からの選択</translation>
    </message>
</context>
<context>
    <name>HelpWindow</name>
    <message>
        <location filename="../src/Help/HelpWindow.cpp" line="34" />
        <source>Contents</source>
        <translation>コンテンツ</translation>
    </message>
    <message>
        <location filename="../src/Help/HelpWindow.cpp" line="36" />
        <source>Index</source>
        <translation>インデックス</translation>
    </message>
</context>
<context>
    <name>LoadImageFromUrl</name>
    <message>
        <location filename="../src/Load/LoadImageFromUrl.cpp" line="63" />
        <source>Unable to download image from</source>
        <translation>画像のダウンロードができません</translation>
    </message>
    <message>
        <location filename="../src/Load/LoadImageFromUrl.cpp" line="95" />
        <source>Unable to load image from</source>
        <translation>画像を取り込むことができません</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="375" />
        <source>Select Tool</source>
        <translation>選択ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="376" />
        <source>Shift+F2</source>
        <translation>Shift+F2</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="378" />
        <source>Select points on screen.</source>
        <translation>画面上でポイントを選択</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="379" />
        <source>Select

Select points on the screen.</source>
        <translation>選択

画面上でポイントを選択</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="383" />
        <source>Axis Point Tool</source>
        <translation>座標軸ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="384" />
        <source>Shift+F3</source>
        <translation>Shift+F3</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="386" />
        <source>Digitize axis points for a graph.</source>
        <translation>グラフ を対象に 座標軸の基準となる ポイント を デジタイズ します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="387" />
        <source>Digitize Axis Point

Digitizes an axis point for a graph by placing a new point at the cursor after a mouse click. The coordinates of the axis point are then entered. In a graph, three axis points are required to define the graph coordinates.</source>
        <translation>座標軸の基準となる ポイント の デジタイズ

グラフ の座標軸の基準となる ポイント を、マウス の クリック で追加するとともに、座標値を入力していきます。グラフ の場合には座標軸を決めるために 3 点 の ポイント が必要になります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="394" />
        <source>Scale Bar Tool</source>
        <translation>スケールバー ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="395" />
        <source>Shift+F8</source>
        <translation>Shift+F8</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="397" />
        <source>Digitize scale bar for a map.</source>
        <translation>マップ を対象に スケールバー を デジタイズ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="398" />
        <source>Digitize Scale Bar

Digitize a scale bar for a map by clicking and dragging. The length of the scale bar is then entered. In a map, the two endpoints of the scale bar define the distances in graph coordinates.

Maps must be imported using Import (Advanced).</source>
        <translation>スケールバー を デジタイズ

マップ を 対象に、スケールバー の位置で マウス を クリック してから ドラッグ します。続いて スケールバー の示す距離を入力してください。 マップ の場合には スケールバー の両端の座標が距離を設定するために使われます。

マップ 画像は、ファイル メニュー の インポート (アドバンス) を選択して インポート してください。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="405" />
        <source>Curve Point Tool</source>
        <translation>カーブ ポイント ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="406" />
        <source>Shift+F4</source>
        <translation>Shift+F4</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="408" />
        <source>Digitize curve points.</source>
        <translation>カーブ の ポイント を デジタイズ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="409" />
        <source>Digitize Curve Point

Digitizes a curve point by placing a new point at the cursor after a mouse click. Use this mode to digitize points along curves one by one.

New points will be assigned to the currently selected curve.</source>
        <translation>カーブ の ポイント を デジタイズ

マウス の クリック で ポイント を追加することで、カーブ の デジタイズ を実行します。この モード で カーブ に沿って ポイント を一つずつ デジタイズ してください。

新たに ポイント をデジタイズ するたびに、それらの ポイント は現在選択中の カーブ に追加されます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="416" />
        <source>Point Match Tool</source>
        <translation>ポイント マッチング ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="417" />
        <source>Shift+F5</source>
        <translation>Shift+F5</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="419" />
        <source>Digitize curve points in a point plot by matching a point.</source>
        <translation>ポイント を マッチング して カーブ 上の ポイント 座標を決定します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="420" />
        <source>Digitize Curve Points by Point Matching

Digitizes curve points in a point plot by finding points that match a sample point. The process starts by selecting a representative sample point.

New points will be assigned to the currently selected curve.</source>
        <translation>ポイント を マッチング して カーブ を デジタイズ

サンプル となる ポイント と マッチング して座標を決定した位置に ポイントを生成します。この処理の最初に 代表となる サンプル ポイント を選択することになります。

新たに 得られた ポイント は現在選択されている カーブ のポイントとなります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="426" />
        <source>Color Picker Tool</source>
        <translation>カラーピッカー ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="427" />
        <source>Shift+F6</source>
        <translation>Shift+F6</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="429" />
        <source>Select color settings for filtering in Segment Fill mode.</source>
        <translation>セグメント フィル モード の色指定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="430" />
        <source>Select color settings for Segment Fill filtering

Select a pixel along the currently selected curve. That pixel and its neighbors will define the filter settings (color, brightness, and so on) of the currently selected curve while in Segment Fill mode.</source>
        <translation>セグメント フィル モード の色指定

現在 選択中の カーブ に沿ってピクセルを選択します。このピクセルおよびその周辺の画像情報 (色・明度等) が セグメント フィル モード で利用されます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="436" />
        <source>Segment Fill Tool</source>
        <translation>セグメント フィル ツール</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="437" />
        <source>Shift+F7</source>
        <translation>Shift+F7</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="439" />
        <source>Digitize curve points along a segment of a curve.</source>
        <translation>カーブの線分とポイントのデジタイズ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="440" />
        <source>Digitize Curve Points With Segment Fill

Digitizes curve points by placing new points along the highlighted segment under the cursor. Use this mode to quickly digitize multiple points along a curve with a single click.

New points will be assigned to the currently selected curve.</source>
        <translation>線分とポイントでカーブをデジタイズします。

カーソル位置に合わせて線分をハイライトし、新たなポイントをデジタイズします。このモードを使うとカーブに沿った複数のポイントを一回のクリックですばやくデジタイズすることができます。

生成された新たなポイントは現在選択されているカーブに追加されます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="461" />
        <source>&amp;Undo</source>
        <translation>やり直し</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="463" />
        <source>Undo the last operation.</source>
        <translation>直前の操作を取り消します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="464" />
        <source>Undo

Undo the last operation.</source>
        <translation>やり直し

直前の操作を取り消します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="468" />
        <source>&amp;Redo</source>
        <translation>繰り返し</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="470" />
        <source>Redo the last operation.</source>
        <translation>直前の操作を再度実行します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="471" />
        <source>Redo

Redo the last operation.</source>
        <translation>繰り返し

直前の操作を再度実行します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="475" />
        <source>Cut</source>
        <translation>カット</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="477" />
        <source>Cuts the selected points and copies them to the clipboard.</source>
        <translation>選択されたポイントを切り取り、クリップボード にコピーします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="478" />
        <source>Cut

Cuts the selected points and copies them to the clipboard.</source>
        <translation>カット

選択されたポイントを切り取り、クリップボード にコピーします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="482" />
        <source>Copy</source>
        <translation>コピー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="484" />
        <source>Copies the selected points to the clipboard.</source>
        <translation>選択されたポイントをクリップボード にコピーします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="485" />
        <source>Copy

Copies the selected points to the clipboard.</source>
        <translation>コピー

選択されたポイントをクリップボード にコピーします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="489" />
        <source>Paste</source>
        <translation>貼り付け</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="491" />
        <source>Pastes the selected points from the clipboard.</source>
        <translation>選択されたポイントをクリップボード からコピーします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="492" />
        <source>Paste

Pastes the selected points from the clipboard. They will be assigned to the current curve.</source>
        <translation>貼り付け

選択されたポイントを クリップボード から貼り付けます。現在のカーブに追加されます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="496" />
        <source>Delete</source>
        <translation>削除</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="498" />
        <source>Deletes the selected points, after copying them to the clipboard.</source>
        <translation>選択された ポイント を クリップボードに コピーしたうえで削除します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="499" />
        <source>Delete

Deletes the selected points, after copying them to the clipboard.</source>
        <translation>削除

選択された ポイント をクリップボードにコピーしたうえで削除します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="503" />
        <source>Paste As New</source>
        <translation>新規画像として貼り付け</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="504" />
        <source>Pastes an image from the clipboard.</source>
        <translation>クリップボード から 画像を貼り付けます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="505" />
        <source>Paste as New

Creates a new document by pasting an image from the clipboard.</source>
        <translation>新規画像として貼り付け

クリップボード から 画像を貼り付けて 新たなドキュメントを作成します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="509" />
        <source>Paste As New (Advanced)...</source>
        <translation>新規画像として貼り付け (アドバンス)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="510" />
        <source>Pastes an image from the clipboard, in advanced mode.</source>
        <translation>アドバンス モード で クリップボード から画像を貼り付けます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="511" />
        <source>Paste as New (Advanced)

Creates a new document by pasting an image from the clipboard, in advanced mode.</source>
        <translation>新規画像として貼り付け (アドバンス)

アドバンス モード で クリップボード から画像を貼り付けます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="520" />
        <source>&amp;Import...</source>
        <translation>インポート</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="521" />
        <source>Ctrl+I</source>
        <translation>Ctrl+I</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="522" />
        <source>Creates a new document by importing an simple image.</source>
        <translation>画像をインポートすることで新たにドキュメントを作成します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="523" />
        <source>Import Image

Creates a new document by importing an image with a single coordinate system, and axes both coordinates known.

For more complicated images with multiple coordinate systems, and/or floating axes, Import (Advanced) is used instead.</source>
        <translation>画像のインポート

画像をインポートして新たにドキュメントを作ります。この画像は既知の2 つの座標軸からなる単一の座標系を持っている必要があります。

複数の座標系からなるさらに複雑な画像を利用する場合あるいは座標軸が変化するような場合には、画像のインポート (アドバンス) を代わりに実行します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="530" />
        <source>Import (Advanced)...</source>
        <translation>画像のインポート (アドバンス)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="531" />
        <source>Creates a new document by importing an image with support for advanced feaures.</source>
        <translation>画像をインポートして新たにドキュメントを作る際に、アドバンス機能を利用します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="532" />
        <source>Import (Advanced)

Creates a new document by importing an image with support for advanced feaures. In advanced mode, there can be multiple coordinate systems and/or floating axes.</source>
        <translation>画像のインポート (アドバンス)

画像をインポートして新たにドキュメントを作る際に、アドバンス機能を利用します。このアドバンス モードでは、複数の座標軸や、変化する座標軸を利用できます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="537" />
        <source>Import (Image Replace)...</source>
        <translation>画像のインポート (差し替え)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="538" />
        <source>Imports a new image into the current document, replacing the existing image.</source>
        <translation>現在のドキュメントに新たな画像をインポートし、既存の画像を差し替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="539" />
        <source>Import (Image Replace)

Imports a new image into the current document. The existing image is replaced, and all curves in the document are preserved. This operation is useful for applying the axis points and other settings from an existing document to a different image.</source>
        <translation>画像のインポート (差し替え)

現在のドキュメントに新たな画像をインポートします。既存の画像は新たな画像に差し替えられますが、ドキュメント内の全てのカーブはそのまま保持されます。この操作は設定を変えずに新たな画像に対して作業を行いたい場合に大変便利です。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="545" />
        <source>&amp;Open...</source>
        <translation>開く</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="547" />
        <source>Opens an existing document.</source>
        <translation>既存のドキュメントを開きます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="548" />
        <source>Open Document

Opens an existing document.</source>
        <translation>開く

既存のドキュメントを開きます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="561" />
        <source>&amp;Close</source>
        <translation>閉じる</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="563" />
        <source>Closes the open document.</source>
        <translation>現在開いているドキュメントを閉じます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="564" />
        <source>Close Document

Closes the open document.</source>
        <translation>閉じる

現在開いているドキュメントを閉じます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="568" />
        <source>&amp;Save</source>
        <translation>上書き保存</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="570" />
        <source>Saves the current document.</source>
        <translation>現在のドキュメントを上書き保存します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="571" />
        <source>Save Document

Saves the current document.</source>
        <translation>上書き保存

現在のドキュメントを上書き保存します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="575" />
        <source>Save As...</source>
        <translation>名前を付けて保存</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="577" />
        <source>Saves the current document under a new filename.</source>
        <translation>現在開いているドキュメントを新たにファイル名をつけて保存します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="578" />
        <source>Save Document As

Saves the current document under a new filename.</source>
        <translation>名前を付けて保存

現在開いているドキュメントを粗らにファイル名をつけて保存します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="582" />
        <source>Export...</source>
        <translation>エクスポート</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="583" />
        <source>Ctrl+E</source>
        <translation>Ctrl+E</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="584" />
        <source>Exports the current document into a text file.</source>
        <translation>現在のドキュメントをテキストファイルとしてエクスポートします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="585" />
        <source>Export Document

Exports the current document into a text file.</source>
        <translation>ドキュメントをエクスポート

現在のドキュメントをテキストファイルとしてエクスポートします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="589" />
        <source>&amp;Print...</source>
        <translation>印刷</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="591" />
        <source>Print the current document.</source>
        <translation>現在のドキュメントを印刷します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="592" />
        <source>Print Document

Print the current document to a printer or file.</source>
        <translation>ドキュメントを印刷

現在のドキュメントをプリンターまたはファイルに出力します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="596" />
        <source>&amp;Exit</source>
        <translation>終了</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="598" />
        <source>Quits the application.</source>
        <translation>アプリケーションを終了します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="599" />
        <source>Exit

Quits the application.</source>
        <translation>終了

アプリケーションを終了します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="608" />
        <source>Checklist Guide Wizard</source>
        <translation>チェックリストと手引きウィザード</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="610" />
        <source>Open Checklist Guide Wizard during import to define digitizing steps</source>
        <translation>インポートの作業の過程で、チェックリストと手引きウィザードを開きます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="611" />
        <source>Checklist Guide Wizard

Use Checklist Guide Wizard during import to generate a checklist of steps for the imported document</source>
        <translation>チェックリストと手引きウィザード

インポートの過程でチェックリストと手引きウィザードを使い、画像をインポートしてドキュメントを作成するための一連の手順のチェックリストを作成します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="618" />
        <source>Tutorial</source>
        <translation>チュートリアル</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="619" />
        <source>Play tutorial showing steps for digitizing curves</source>
        <translation>カーブ をデジタイズ する手順を チュートリアル形式で実行します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="620" />
        <source>Tutorial

Play tutorial showing steps for digitizing points from curves drawn with lines and/or point</source>
        <translation>チュートリアル

カーブ をデジタイズ する手順をチュートリアル形式で実行します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="626" />
        <source>Help</source>
        <translation>ヘルプ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="628" />
        <source>Help documentation</source>
        <translation>ヘルプ ドキュメント</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="629" />
        <source>Help Documentation

Searchable help documentation</source>
        <translation>ヘルプ ドキュメント

検索可能なヘルプ ドキュメント</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="634" />
        <source>About Engauge</source>
        <translation>Engaugeについて</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="635" />
        <source>About the application.</source>
        <translation>このアプリケーションについて</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="636" />
        <source>About Engauge

About the application.</source>
        <translation>Engaugeについて

このアプリケーションについて</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="644" />
        <source>Coordinates...</source>
        <translation>座標系</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="645" />
        <source>Edit Coordinate settings.</source>
        <translation>座標系の設定を編集します</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="646" />
        <source>Coordinate Settings

Coordinate settings determine how the graph coordinates are mapped to the pixels in the image</source>
        <translation>座標系の設定

座標系の設定はグラフに設定した座標がどのように画像上のピクセル位置に対応するかを定めます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="650" />
        <source>Add/Remove Curve...</source>
        <translation>カーブの追加/削除</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="651" />
        <source>Add or Remove Curves.</source>
        <translation>カーブを追加または削除します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="652" />
        <source>Add/Remove Curve

Add/Remove Curve settings control which curves are included in the current document</source>
        <translation>カーブ の追加/削除

ドキュメント中に含む カーブ の追加あるいは削除を行います。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="656" />
        <source>Curve Properties...</source>
        <translation>カーブ 設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="657" />
        <source>Edit Curve Properties settings.</source>
        <translation>カーブ の設定を行います。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="658" />
        <source>Curve Properties Settings

Curves properties settings determine how each curve appears</source>
        <translation>カーブ 設定

カーブ 設定では、それぞれの カーブ をどのように表示するかを設定します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="662" />
        <source>Digitize Curve...</source>
        <translation>カーブ を デジタイズ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="663" />
        <source>Edit Digitize Axis and Graph Curve settings.</source>
        <translation>座標軸 および グラフ 設定の編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="664" />
        <source>Digitize Axis and Graph Curve Settings

Digitize Curve settings determine how points are digitized in Digitize Axis Point and Digitize Graph Point modes</source>
        <translation>デジタイズ 設定の編集

デジタイズ 設定は座標軸上の基準点やカーブ ポイント をデジタイズする際の設定を行います。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="669" />
        <source>Export Format...</source>
        <translation>エクスポート フォーマット</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="670" />
        <source>Edit Export Format settings.</source>
        <translation>エクスポート フォーマット の編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="671" />
        <source>Export Format Settings

Export format settings affect how exported files are formatted</source>
        <translation>エクスポート フォーマット 設定

エクスポートされたファイルのフォーマットを指定します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="675" />
        <source>Color Filter...</source>
        <translation>カラー フィルター</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="676" />
        <source>Edit Color Filter settings.</source>
        <translation>カラー フィルター 設定の編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="677" />
        <source>Color Filter Settings

Color filtering simplifies the graphs for easier Point Matching and Segment Filling</source>
        <translation>カラー フィルター 設定

カラー フィルター により、 ポイント マッチング や セグメント フィル の処理に際して グラフの認識がより効率的になります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="681" />
        <source>Axes Checker...</source>
        <translation>座標軸 チェッカー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="682" />
        <source>Edit Axes Checker settings.</source>
        <translation>座標軸 チェッカー の設定を編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="683" />
        <source>Axes Checker Settings

Axes checker can reveal any axis point mistakes, which are otherwise hard to find.</source>
        <translation>座標軸 チェッカー の設定

座標軸 チェッカー により、座標軸の基準点に問題がないかどうかを確認することができます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="687" />
        <source>Grid Line Display...</source>
        <translation>グリッド 線の表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="688" />
        <source>Edit Grid Line Display settings.</source>
        <translation>グリット 線の表示設定を編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="689" />
        <source>Grid Line Display Settings

Grid lines displayed on the graph can provide more accuracy than the Axis Checker, for distorted graphs. In a distorted graph, the grid lines can be used to adjust the axis points for more accuracy in different regions.</source>
        <translation>グリッド 線の表示設定

グラフ上にグリッド 線を表示すると、座標軸 チェッカー よりもさらに正確に グラフ の歪みなどをチェックすることができます。グラフの画像が歪んでいる場合には、グリッド 線を利用して座標軸の基準点を微調整することで、グラフ の各部分にわたって精度を上げることができます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="694" />
        <source>Grid Line Removal...</source>
        <translation>グリッド 線の除去</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="695" />
        <source>Edit Grid Line Removal settings.</source>
        <translation>グリッド 線の除去機能の設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="696" />
        <source>Grid Line Removal Settings

Grid line removal isolates curve lines for easier Point Matching and Segment Filling, when Color Filtering is not able to separate grid lines from curve lines.</source>
        <translation>グリッド 線の除去機能の設定

特に カラー フィルター がグリッド 線と カーブ を区別できないときなど、カーブ の線を残してグリッド 線を除去することで、ポイント マッチング やセグメント フィル 処理が容易になります。 </translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="701" />
        <source>Point Match...</source>
        <translation>ポイント マッチング</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="702" />
        <source>Edit Point Match settings.</source>
        <translation>ポイント マッチング 設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="703" />
        <source>Point Match Settings

Point match settings determine how points are matched while in Point Match mode</source>
        <translation>ポイント マッチング 設定

ポイント マッチング 設定では ポイント マッチング モード でどのようにポイント を認識するか を指定します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="707" />
        <source>Segment Fill...</source>
        <translation>セグメント フィル</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="708" />
        <source>Edit Segment Fill settings.</source>
        <translation>セグメント フィル 設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="709" />
        <source>Segment Fill Settings

Segment fill settings determine how points are generated in the Segment Fill mode</source>
        <translation>セグメント フィル 設定

セグメント フィル 設定では、セグメント フィル モードでどのように ポイント を決定するかを指定します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="713" />
        <source>General...</source>
        <translation>一般設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="714" />
        <source>Edit General settings.</source>
        <translation>全般的な設定を行います。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="715" />
        <source>General Settings

General settings are document-specific settings that affect multiple modes. For example, the cursor size setting affects both Color Picker and Point Match modes</source>
        <translation>一般設定

一般設定では、それぞれのドキュメントについて複数のモードに影響を及ぼす設定を行います。 例えば、カーソル サイズの 設定は カラーピッカー と ポイントマッチ モード に影響します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="720" />
        <source>Main Window...</source>
        <translation>メイン画面</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="722" />
        <source>Edit Main Window settings.</source>
        <translation>メイン画面 の設定を編集します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="723" />
        <source>Main Window Settings

Main window settings affect the user interface and are not specific to any document</source>
        <translation>メイン画面 の設定

メイン画面 の設定はユーザーインターフェースに関するもので、特定のドキュメントに関わる設定項目ではありません。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="732" />
        <source>Background Toolbar</source>
        <translation>バックグラウンド ツールバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="735" />
        <source>Show or hide the background toolbar.</source>
        <translation>バックグラウンド ツールバー の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="736" />
        <source>View Background ToolBar

Show or hide the background toolbar</source>
        <translation>バックグラウンド ツールバー

バックグラウンド ツールバー の表示・非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="740" />
        <source>Checklist Guide Toolbar</source>
        <translation>チェックリスト と手引き ツールバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="743" />
        <source>Show or hide the checklist guide.</source>
        <translation>チェックリスト と手引き の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="744" />
        <source>View Checklist Guide

Show or hide the checklist guide</source>
        <translation>チェックリスト と手引き の表示

チェックリスト と手引き の表示・非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="748" />
        <source>Curve Fitting Window</source>
        <translation>カーブ フィッティング 画面</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="751" />
        <source>Show or hide the curve fitting window.</source>
        <translation>カーブ フィッティング 画面の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="752" />
        <source>View Curve Fitting Window

Show or hide the curve fitting window</source>
        <translation>カーブ フィッティング 画面

カーブ フィッティング 画面の表示・非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="756" />
        <source>Geometry Window</source>
        <translation>カーブ の形状画面</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="759" />
        <source>Show or hide the geometry window.</source>
        <translation>カーブ の形状画面の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="760" />
        <source>View Geometry Window

Show or hide the geometry window</source>
        <translation>カーブ の形状画面

カーブ の形状画面の表示・非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="764" />
        <source>Digitizing Tools Toolbar</source>
        <translation>デジタイズ ツール ツールバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="767" />
        <source>Show or hide the digitizing tools toolbar.</source>
        <translation>デジタイズ ツール の ツールバー の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="768" />
        <source>View Digitizing Tools ToolBar

Show or hide the digitizing tools toolbar</source>
        <translation>デジタイズ ツール ツールバー

デジタイズ ツール ツールバー の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="772" />
        <source>Settings Views Toolbar</source>
        <translation>設定 ビュー ツールバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="775" />
        <source>Show or hide the settings views toolbar.</source>
        <translation>設定 ビュー ツールバー の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="776" />
        <source>View Settings Views ToolBar

Show or hide the settings views toolbar. These views graphically show the most important settings.</source>
        <translation>設定 ビュー ツールバー

設定 ビュー ツールバー の表示・非表示を切り替えます。これらの ビュー では 最も重要な設定を画像として確認することができます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="781" />
        <source>Coordinate System Toolbar</source>
        <translation>座標系 ツールバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="784" />
        <source>Show or hide the coordinate system toolbar.</source>
        <translation>座標系 ツールバー の表示 非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="785" />
        <source>View Coordinate Systems ToolBar

Show or hide the coordinate system selection toolbar. This toolbar is used to select the current coordinate system when the document has multiple coordinate systems. This toolbar is also used to view and print all coordinate systems.

This toolbar is disabled when there is only one coordinate system.</source>
        <translation>座標系 ツールバー の表示

座標系 を選択するための ツールバーの 表示 非表示 を切り替えます。この ツールバー はドキュメントが複数の 座標系 をもつ場合に、座標系 を選択するために使用します。この ツールバー はまた全ての 座標系 を表示したり印刷したりするためにも使用します。

この ツールバー は、座標系 が一つしかないときにはアクティブになりません。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="793" />
        <source>Tool Tips</source>
        <translation>ツール ティップ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="796" />
        <source>Show or hide the tool tips.</source>
        <translation>ツール ティップ の表示・非表示の切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="797" />
        <source>View Tool Tips

Show or hide the tool tips</source>
        <translation>ツール ティップ

ツール ティップ の表示・非表示を切り替えます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="801" />
        <source>Grid Lines</source>
        <translation>グリッド 線</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="804" />
        <source>Show or hide grid lines.</source>
        <translation>グリッド 線の表示・非表示を切り替え</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="805" />
        <source>View Grid Lines

Show or hide grid lines that are added for accurate adjustments of the axes points, which can improve accuracy in distorted graphs</source>
        <translation>グリッド 線の表示

グリッド 線の表示・非表示を切り替えます。グリッド 線は座標軸の基準点を微調整するために利用すると、特に画像が歪んだ グラフ を デジタイズ するときの精度の向上に役立ちます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="810" />
        <source>No Background</source>
        <translation>バックグラウンド 画像なし</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="812" />
        <source>Do not show the image underneath the points.</source>
        <translation>ポイント の背景に 画像を表示しません。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="813" />
        <source>No Background

No image is shown so points are easier to see</source>
        <translation>バックグラウンド 画像なし

背景に画像を表示せず、ポイントをより視認しやすくします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="816" />
        <source>Show Original Image</source>
        <translation>オリジナル画像を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="818" />
        <source>Show the original image underneath the points.</source>
        <translation>ポイントの背景としてオリジナル画像を表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="819" />
        <source>Show Original Image

Show the original image underneath the points</source>
        <translation>オリジナル画像を表示

ポイントの背景としてオリジナル画像を表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="822" />
        <source>Show Filtered Image</source>
        <translation>フィルタ 処理された画像</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="825" />
        <source>Show the filtered image underneath the points.</source>
        <translation>ポイント の背景に フィルタ 処理された画像を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="826" />
        <source>Show Filtered Image

Show the filtered image underneath the points.

The filtered image is created from the original image according to the Filter preferences so unimportant information is hidden and important information is emphasized</source>
        <translation>フィルタ処理された背景画像

ポイントの背景にフィルタ処理された画像を表示

フィルタに関する設定に基づきオリジナル画像をフィルタ処理したものを背景として利用します。画像に含まれる重要ではない情報を除くことで、重要な情報を強調する狙いがあります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="832" />
        <source>Hide All Curves</source>
        <translation>全てのカーブを非表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="834" />
        <source>Hide all digitized curves.</source>
        <translation>全てのカーブを非表示にします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="835" />
        <source>Hide All Curves

No axis points or digitized graph curves are shown so the image is easier to see.</source>
        <translation>全てのカーブを非表示

座標軸の基準点やデジタイズされたカーブを全て非表示にしますので、画像が見やすくなります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="838" />
        <source>Show Selected Curve</source>
        <translation>選択中のカーブを表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="840" />
        <source>Show only the currently selected curve.</source>
        <translation>現在選択されているカーブのみを表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="841" />
        <source>Show Selected Curve

Show only the digitized points and line that belong to the currently selected curve.</source>
        <translation>選択中のカーブを表示

デジタイズされたポイントとラインのうち、現在選択中のカーブに属するものだけを表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="844" />
        <source>Show All Curves</source>
        <translation>全てのカーブを表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="847" />
        <source>Show all curves.</source>
        <translation>全てのカーブを表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="848" />
        <source>Show All Curves

Show all digitized axis points and graph curves</source>
        <translation>全てのカーブを表示

デジタイズされた座標軸とグラフの全てのポイントとカーブを表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="863" />
        <source>Hide Always</source>
        <translation>常に非表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="865" />
        <source>Always hide the status bar.</source>
        <translation>ステータスバーを常に非表示にします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="866" />
        <source>Hide the status bar. No temporary status or feedback messages will appear.</source>
        <translation>ステータスバー を非表示とし、ステータス情報や メッセージ が表示されなくなります。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="868" />
        <source>Show Temporary Messages</source>
        <translation>メッセージ を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="870" />
        <source>Hide the status bar except when display temporary messages.</source>
        <translation>メッセージ があるとき以外ステータスバー を非表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="871" />
        <source>Hide the status bar, except when displaying temporary status and feedback messages.</source>
        <translation>メッセージ があるときを除いて ステータスバー を非表示とします。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="873" />
        <source>Show Always</source>
        <translation>常に表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="875" />
        <source>Always show the status bar.</source>
        <translation>ステータスバーを常に表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="876" />
        <source>Show the status bar. Besides displaying temporary status and feedback messages, the status bar also displays information about the cursor position.</source>
        <translation>ステータスバー を表示します。ステータスバー には実行状況やフェードバック メッセージに加えて、カーソルの位置における情報も表示されます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="885" />
        <source>Zoom Out</source>
        <translation>縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="886" />
        <source>Zoom out</source>
        <translation>縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="890" />
        <source>Zoom In</source>
        <translation>拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="891" />
        <source>Zoom in</source>
        <translation>拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="898" />
        <source>16:1 (1600%)</source>
        <translation>16:1 (1600%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="900" />
        <source>Zoom 16:1</source>
        <translation>倍率を16:1倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="904" />
        <source>16:1 farther (1270%)</source>
        <translation>16:1 よりやや遠望 (1270%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="906" />
        <source>Zoom 12.7:1</source>
        <translation>倍率を 12.7:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="910" />
        <source>8:1 closer (1008%)</source>
        <translation>8:1 よりやや近接 (1008%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="912" />
        <source>Zoom 10.08:1</source>
        <translation>倍率を 10.08:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="916" />
        <source>8:1 (800%)</source>
        <translation>8:1 (800%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="918" />
        <source>Zoom 8:1</source>
        <translation>倍率を8:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="922" />
        <source>8:1 farther (635%)</source>
        <translation>8:1 よりやや遠望 (635%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="924" />
        <source>Zoom 6.35:1</source>
        <translation>倍率を 6.35:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="928" />
        <source>4:1 closer (504%)</source>
        <translation>4:1 よりやや近接 (504%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="930" />
        <source>Zoom 5.04:1</source>
        <translation>倍率を 5.04:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="934" />
        <source>4:1 (400%)</source>
        <translation>4:1 (400%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="936" />
        <source>Zoom 4:1</source>
        <translation>倍率を 4:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="940" />
        <source>4:1 farther (317%)</source>
        <translation>4:1 よりやや遠望 (317%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="942" />
        <source>Zoom 3.17:1</source>
        <translation>倍率を 3.17:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="946" />
        <source>2:1 closer (252%)</source>
        <translation>2:1 よりやや近接 (252%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="948" />
        <source>Zoom 2.52:1</source>
        <translation>倍率を 2.52:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="952" />
        <source>2:1 (200%)</source>
        <translation>2:1 (200%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="954" />
        <source>Zoom 2:1</source>
        <translation>倍率を 2:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="958" />
        <source>2:1 farther (159%)</source>
        <translation>2:1 よりやや遠望 (159%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="960" />
        <source>Zoom 1.59:1</source>
        <translation>倍率を 1.59:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="964" />
        <source>1:1 closer (126%)</source>
        <translation>1:1 よりやや近接 (126%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="967" />
        <source>Zoom 1.3:1</source>
        <translation>倍率を 1.3:1 倍に拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="971" />
        <source>1:1 (100%)</source>
        <translation>1:1 (100%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="974" />
        <source>Zoom 1:1</source>
        <translation>倍率を 1:1 の等倍に</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="978" />
        <source>1:1 farther (79%)</source>
        <translation>1:1 よりやや遠望 (79%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="981" />
        <source>Zoom 0.8:1</source>
        <translation>倍率を 0.8:1 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="985" />
        <source>1:2 closer (63%)</source>
        <translation>1:2 よりやや近接 (63%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="987" />
        <source>Zoom 1.3:2</source>
        <translation>倍率を 1.3:2 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="991" />
        <source>1:2 (50%)</source>
        <translation>1:2 (50%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="993" />
        <source>Zoom 1:2</source>
        <translation>倍率を 1:2 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="997" />
        <source>1:2 farther (40%)</source>
        <translation>1:2 よりやや遠望 (40%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="999" />
        <source>Zoom 0.8:2</source>
        <translation>倍率を 0.8:2 倍に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1003" />
        <source>1:4 closer (31%)</source>
        <translation>1:4 よりやや遠望 (31%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1005" />
        <source>Zoom 1.3:4</source>
        <translation>倍率を 1.3:4 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1009" />
        <source>1:4 (25%)</source>
        <translation>1:4 (25%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1011" />
        <source>Zoom 1:4</source>
        <translation>倍率を 1:4 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1015" />
        <source>1:4 farther (20%)</source>
        <translation>1:4 よりやや遠望 (20%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1017" />
        <source>Zoom 0.8:4</source>
        <translation>倍率を 0.8:4 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1021" />
        <source>1:8 closer (12.5%)</source>
        <translation>1:8 よりやや近接 (12.5%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1023" />
        <location filename="../src/main/MainWindow.cpp" line="1029" />
        <source>Zoom 1:8</source>
        <translation>倍率を 1:8 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1027" />
        <source>1:8 (12.5%)</source>
        <translation>1:8 (12.5%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1033" />
        <source>1:8 farther (10%)</source>
        <translation>1:8 よりやや遠望 (10%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1035" />
        <source>Zoom 0.8:8</source>
        <translation>倍率を 0.8:8 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1039" />
        <source>1:16 closer (8%)</source>
        <translation>1:16 よりやや近接 (8%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1041" />
        <source>Zoom 1.3:16</source>
        <translation>倍率を 1.3:16 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1045" />
        <source>1:16 (6.25%)</source>
        <translation>1:16 (6.25%)</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1047" />
        <source>Zoom 1:16</source>
        <translation>倍率を 1:16 に縮小</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1051" />
        <source>Fill</source>
        <translation>フィル</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1053" />
        <source>Zoom with stretching to fill window</source>
        <translation>画面サイズに合わせて拡大</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1171" />
        <source>&amp;File</source>
        <translation>ファイル</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1177" />
        <source>Open &amp;Recent</source>
        <translation>最近使ったドキュメント</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1193" />
        <source>&amp;Edit</source>
        <translation>編集</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1206" />
        <source>Digitize</source>
        <translation>デジタイズ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1215" />
        <source>View</source>
        <translation>ビュー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1227" />
        <location filename="../src/main/MainWindow.cpp" line="1411" />
        <source>Background</source>
        <translation>バックグラウンド</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1232" />
        <source>Curves</source>
        <translation>カーブ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1237" />
        <source>Status Bar</source>
        <translation>ステータスバー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1242" />
        <source>Zoom</source>
        <translation>拡大率</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1274" />
        <source>Settings</source>
        <translation>設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1290" />
        <source>&amp;Help</source>
        <translation>ヘルプ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1398" />
        <source>Select background image</source>
        <translation>バックグラウンド画像の選択</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1399" />
        <source>Selected Background

Select background image:
1) No background which highlights points
2) Original image which shows everything
3) Filtered image which highlights important details</source>
        <translation>バックグラウンド 画像の選択

バックグラウンド 画像を以下から選択します：
1) バックグラウンド 画像をなくしてポイントを明瞭に見せます
2) オリジナル 画像を表示します
3) フィルタ処理された画像で重要な部分を詳細に見せます</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1404" />
        <source>No background</source>
        <translation>バックグラウンド画像なし</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1405" />
        <source>Original image</source>
        <translation>オリジナル画像を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1406" />
        <source>Filtered image</source>
        <translation>フィルタ処理された画像を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1419" />
        <source>Select curve for new points.</source>
        <translation>ポイント を追加する 対象の カーブ を選択</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1420" />
        <source>Selected Curve Name

Select curve for any new points. Every point belongs to one curve.

This can be changed while in Curve Point, Point Match, Color Picker or Segment Fill mode.</source>
        <translation>カーブ 名の選択

新たに ポイントを 追加する対象の カーブ を選択します。すべてのポイント は カーブ に帰属します。

選択された カーブ は カーブ の ポイント 追加、ポイント マッチング 、カラーピッカー、セグメント フィル モード のいずれにおいても 変更可能です。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1426" />
        <source>Drawing</source>
        <translation>描画設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1443" />
        <source>Points style for the currently selected curve</source>
        <translation>選択された カーブ の ポイント の表示スタイル</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1444" />
        <source>Points Style

Points style for the currently selected curve. The points style is only displayed in this toolbar. To change the points style, use the Curve Properties dialog.</source>
        <translation>ポイント の表示スタイル

選択された カーブ の ポイント の表示スタイル を設定します。このツールバー ではポイント の スタイルが表示されるだけなので、スタイル を変更するには カーブ の プロパティ 画面を利用してください。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1452" />
        <source>View of filter for current curve in Segment Fill mode</source>
        <translation>セグメント フィル モード での現在の カーブ に対するフィルタ設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1453" />
        <source>Segment Fill Filter

View of filter for the current curve in Segment Fill mode. The filter settings are only displayed in this toolbar. To changed the filter settings, use the Color Picker mode or the Filter Settings dialog.</source>
        <translation>セグメント フィル フィルター

セグメント フィル モード で現在選択中の カーブ に対するフィルタ設定を確認します。この ツールバーでは設定の確認のみが可能ですのでフィルタ設定を変更するには カラーピッカー モード またはフィルタ 設定画面を利用してください。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1459" />
        <source>Views</source>
        <translation>ビュー</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1468" />
        <source>Currently selected coordinate system</source>
        <translation>現在の座標系</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1469" />
        <source>Selected Coordinate System

Currently selected coordinate system. This is used to switch between coordinate systems in documents with multiple coordinate systems</source>
        <translation>現在の座標系

現在 設定されている座標系を表示します。ドキュメントによりますが複数の座標系を切り替えることが可能です。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1477" />
        <source>Show all coordinate systems</source>
        <translation>全ての座標系を表示</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1478" />
        <source>Show All Coordinate Systems

When pressed and held, this button shows all digitized points and lines for all coordinate systems.</source>
        <translation>全ての座標系を表示

このボタンを長押しすることで全ての座標系においてデジタイズされたポイントやラインを表示することができます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1486" />
        <source>Print all coordinate systems</source>
        <translation>全ての 座標系を印刷</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1487" />
        <source>Print All Coordinate Systems

When pressed, this button Prints all digitized points and lines for all coordinate systems.</source>
        <translation>全ての座標系を印刷

このボタンを押すころで座標系に関わらずデジタイズされた全ての ポイント と ライン を印刷することができます。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1491" />
        <source>Coordinate System</source>
        <translation>座標系</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1662" />
        <source>Unable to export to file </source>
        <translation>ファイルのエクスポートに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1737" />
        <location filename="../src/main/MainWindow.cpp" line="1865" />
        <location filename="../src/main/MainWindow.cpp" line="2033" />
        <source>Cannot read file</source>
        <translation>ファイルを読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1739" />
        <location filename="../src/main/MainWindow.cpp" line="1867" />
        <location filename="../src/main/MainWindow.cpp" line="2035" />
        <source>from directory</source>
        <translation>指定のディレクトリから</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="1819" />
        <source>Import Image</source>
        <translation>画像を インポート</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2010" />
        <source>File opened</source>
        <translation>ファイルが開かれた</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2055" />
        <source>File not found:</source>
        <translation>ファイル が見つかりません。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2072" />
        <source>Error report opened</source>
        <translation type="unfinished" />
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2130" />
        <location filename="../src/main/MainWindow.cpp" line="2204" />
        <source>File imported</source>
        <translation>ファイル をインポートしました。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2238" />
        <source>Background image.</source>
        <translation>バックグラウンド 画像</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2239" />
        <source>Currently selected curve.</source>
        <translation>現在 選択中の カーブ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2240" />
        <source>Point style for currently selected curve.</source>
        <translation>現在 選択中の カーブの ポイント 表示設定</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2241" />
        <source>Segment Fill filter for currently selected curve.</source>
        <translation>現在 選択中の カーブに対する セグメント フィル フィルタ </translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2289" />
        <source>The document has been modified.
Do you want to save your changes?</source>
        <translation>ドキュメントの内容が変更されました。
変更を保存しますか？</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="2373" />
        <source>Cannot write file</source>
        <translation>ファイル への書き込みに失敗しました。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="3412" />
        <source>Export</source>
        <translation>エクスポート</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="3490" />
        <source>Open Document</source>
        <translation>ドキュメントを開く</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="4693" />
        <source>+</source>
        <translation>+</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="4694" />
        <source>-</source>
        <translation>-</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="4822" />
        <source>Engauge Digitizer %1</source>
        <translation>Engauge Digitizer %1</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="126" />
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="171" />
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="267" />
        <source>New axis point cannot be at the same screen position as an existing axis point</source>
        <translation>すでに存在する座標軸の基準点と画面上の同じ位置に、新たに基準点を追加することはできません。</translation>
    </message>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="179" />
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="274" />
        <source>New axis point cannot have the same graph coordinates as an existing axis point</source>
        <translation>すでに存在する座標軸の基準点とグラフ上同じとなる位置に、新たに基準点を追加することはできません。</translation>
    </message>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="185" />
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="280" />
        <source>No more than two axis points can lie along the same line on the screen</source>
        <translation>画面上で同じ ライン 上に 2 点を超える 座標軸の基準点を与えることはできません。</translation>
    </message>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="191" />
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="286" />
        <source>No more than two axis points can lie along the same line in graph coordinates</source>
        <translation>グラフ座標で同じ ライン 上に 2 点を超える座標軸の基準点を与えることはできません。</translation>
    </message>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="244" />
        <source>Too many x axis points. There should only be two</source>
        <translation> X 軸の基準点が多すぎます。基準点は 2 点のみ必要です。</translation>
    </message>
    <message>
        <location filename="../src/Callback/CallbackAxisPointsAbstract.cpp" line="250" />
        <source>Too many y axis points. There should only be two</source>
        <translation> Y 軸の基準点が多すぎます。基準点は 2 点のみ必要です。</translation>
    </message>
    <message>
        <location filename="../src/Checker/CheckerMode.cpp" line="14" />
        <source>Never</source>
        <translation>表示なし</translation>
    </message>
    <message>
        <location filename="../src/Checker/CheckerMode.cpp" line="17" />
        <source>NSeconds</source>
        <translation>指定秒数</translation>
    </message>
    <message>
        <location filename="../src/Checker/CheckerMode.cpp" line="20" />
        <source>Forever</source>
        <translation>継続表示</translation>
    </message>
    <message>
        <location filename="../src/Checker/CheckerMode.cpp" line="23" />
        <location filename="../src/Color/ColorFilterMode.cpp" line="29" />
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="28" />
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="49" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="36" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="65" />
        <location filename="../src/Curve/CurveConnectAs.cpp" line="30" />
        <location filename="../src/Export/ExportDelimiter.cpp" line="26" />
        <location filename="../src/Export/ExportHeader.cpp" line="23" />
        <location filename="../src/Export/ExportLayoutFunctions.cpp" line="20" />
        <location filename="../src/Export/ExportPointsIntervalUnits.cpp" line="20" />
        <location filename="../src/Export/ExportPointsSelectionFunctions.cpp" line="26" />
        <location filename="../src/Export/ExportPointsSelectionRelations.cpp" line="20" />
        <location filename="../src/Grid/GridCoordDisable.cpp" line="26" />
        <location filename="../src/Point/PointShape.cpp" line="32" />
        <source>Unknown</source>
        <translation>不明</translation>
    </message>
    <message>
        <location filename="../src/Checklist/ChecklistGuideWizard.cpp" line="69" />
        <source>Curves for coordinate system</source>
        <translation>座標系の基準</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdAddPointsGraph.cpp" line="51" />
        <location filename="../src/FileCmd/FileCmdExport.cpp" line="29" />
        <location filename="../src/FileCmd/FileCmdImport.cpp" line="29" />
        <location filename="../src/FileCmd/FileCmdOpen.cpp" line="29" />
        <source>Missing attribute</source>
        <translation>情報の不足</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdAddPointsGraph.cpp" line="93" />
        <location filename="../src/Cmd/CmdEditPointGraph.cpp" line="105" />
        <source>Cannot read graph points</source>
        <translation>グラフ のポイント を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdCopy.cpp" line="66" />
        <location filename="../src/Cmd/CmdDelete.cpp" line="63" />
        <location filename="../src/Cmd/CmdEditPointAxis.cpp" line="60" />
        <location filename="../src/Cmd/CmdEditPointGraph.cpp" line="60" />
        <location filename="../src/Cmd/CmdMoveBy.cpp" line="62" />
        <source>Missing attribute(s)</source>
        <translation>情報の不足</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdCopy.cpp" line="69" />
        <location filename="../src/Cmd/CmdCut.cpp" line="70" />
        <location filename="../src/Cmd/CmdDelete.cpp" line="66" />
        <location filename="../src/Cmd/CmdEditPointAxis.cpp" line="66" />
        <location filename="../src/Cmd/CmdEditPointGraph.cpp" line="64" />
        <location filename="../src/Cmd/CmdMoveBy.cpp" line="64" />
        <source>and/or</source>
        <translation>及び あるいは</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdCut.cpp" line="67" />
        <source>Missing argument(s)</source>
        <translation>情報の不足</translation>
    </message>
    <message>
        <location filename="../src/Cmd/CmdSettingsAxesChecker.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsColorFilter.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsCoords.cpp" line="51" />
        <location filename="../src/Cmd/CmdSettingsCurveAddRemove.cpp" line="78" />
        <location filename="../src/Cmd/CmdSettingsCurveProperties.cpp" line="51" />
        <location filename="../src/Cmd/CmdSettingsDigitizeCurve.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsExportFormat.cpp" line="51" />
        <location filename="../src/Cmd/CmdSettingsGeneral.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsGridDisplay.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsGridRemoval.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsPointMatch.cpp" line="50" />
        <location filename="../src/Cmd/CmdSettingsSegments.cpp" line="50" />
        <source>Reached end of file before finding end element for</source>
        <translation>ファイルの最後まで確認しましたが最終項目を特定できませんでした。</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterMode.cpp" line="14" />
        <source>Foreground</source>
        <translation>前面</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterMode.cpp" line="17" />
        <source>Hue</source>
        <translation>色相</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterMode.cpp" line="20" />
        <source>Intensity</source>
        <translation>明度</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterMode.cpp" line="23" />
        <source>Saturation</source>
        <translation>彩度</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterMode.cpp" line="26" />
        <source>Value</source>
        <translation>値</translation>
    </message>
    <message>
        <location filename="../src/Color/ColorFilterSettings.cpp" line="214" />
        <source>Cannot read curve filter data</source>
        <translation>カーブ の値を読み取ることができません。</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsDate.cpp" line="14" />
        <source>DD/MM/YYYY</source>
        <translation>DD/MM/YYYY</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsDate.cpp" line="17" />
        <source>MM/DD/YYYY</source>
        <translation>MM/DD/YYYY</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsDate.cpp" line="20" />
        <source>YYYY/MM/DD</source>
        <translation>YYYY/MM/DD</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsDate.cpp" line="26" />
        <location filename="../src/Coord/CoordUnitsTime.cpp" line="23" />
        <source>unknown</source>
        <translation>不明</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="16" />
        <source>Date Time</source>
        <translation>日付 / 時刻</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="19" />
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="22" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="15" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="18" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="21" />
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="24" />
        <source>Degrees</source>
        <translation>度</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="25" />
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="46" />
        <source>Number</source>
        <translation>数値</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsNonPolarTheta.cpp" line="37" />
        <source>Date/Time</source>
        <translation>日付 / 時刻</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="27" />
        <source>Gradians</source>
        <translation>グラディアン</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="30" />
        <source>Radians</source>
        <translation>ラジアン</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsPolarTheta.cpp" line="33" />
        <source>Turns</source>
        <translation>回転</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsTime.cpp" line="14" />
        <source>HH:MM</source>
        <translation>HH:MM</translation>
    </message>
    <message>
        <location filename="../src/Coord/CoordUnitsTime.cpp" line="17" />
        <source>HH:MM:SS</source>
        <translation>HH:MM:SS</translation>
    </message>
    <message>
        <location filename="../src/CoordSystem/CoordSystem.cpp" line="572" />
        <source>Unexpected xml token</source>
        <translation>予想外の xmlトークン</translation>
    </message>
    <message>
        <location filename="../src/Curve/Curve.cpp" line="367" />
        <location filename="../src/Curve/Curve.cpp" line="419" />
        <source>Cannot read curve data</source>
        <translation>カーブ の データ を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveConnectAs.cpp" line="15" />
        <source>FunctionSmooth</source>
        <translation>曲線で内挿</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveConnectAs.cpp" line="18" />
        <source>FunctionStraight</source>
        <translation>直線で内挿</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveConnectAs.cpp" line="21" />
        <source>RelationSmooth</source>
        <translation>ポイント 間を順に曲線で内挿</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveConnectAs.cpp" line="24" />
        <source>RelationStraight</source>
        <translation>ポイント 間を順に直線で内挿</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveConnectAs.cpp" line="27" />
        <source>ConnectSkipForAxisCurve</source>
        <translation>座標軸 の基準線接続をスキップ</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurveStyle.cpp" line="69" />
        <source>Cannot read curve style data</source>
        <translation>カーブ の表示設定を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurvesGraphs.cpp" line="223" />
        <source>DUPLICATE</source>
        <translation>複製</translation>
    </message>
    <message>
        <location filename="../src/Curve/CurvesGraphs.cpp" line="237" />
        <source>Cannot read graph curves data</source>
        <translation>カーブ データ を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateAxis.cpp" line="135" />
        <location filename="../src/DigitizeState/DigitizeStateAxis.cpp" line="176" />
        <location filename="../src/DigitizeState/DigitizeStateScale.cpp" line="173" />
        <source>Engauge Digitizer</source>
        <translation>Engauge Digitizer</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateAxis.cpp" line="136" />
        <source>Three axis points have been defined, and no more are needed or allowed.</source>
        <translation>座標軸 を設定するための3つの基準ポイントが既に設定されたので、ポイント の追加は不要です。</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateColorPicker.cpp" line="151" />
        <source>Color Picker</source>
        <translation>カラーピッカー</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateColorPicker.cpp" line="152" />
        <source>Sorry, but the color picker point must be near a non-background pixel. Please try again.</source>
        <translation>申し訳ありませんが カラーピッカー で選べる ポイント は バックグラウンド ではない ピクセル値  が必要です。再度試してみてください。</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStatePointMatch.cpp" line="350" />
        <source>Point Match</source>
        <translation>ポイント マッチング</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStatePointMatch.cpp" line="351" />
        <source>There are no more matching points</source>
        <translation>これ以上 マッチング できる ポイントがありません。</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateScale.cpp" line="174" />
        <source>The scale bar has been defined, and another is not needed or allowed.</source>
        <translation>スケールバー が既に設定済みですので、改めて設定する必要がありません。</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateSelect.cpp" line="35" />
        <source>Move down</source>
        <translation>下へ 移動</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateSelect.cpp" line="36" />
        <source>Move left</source>
        <translation>左へ 移動</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateSelect.cpp" line="37" />
        <source>Move right</source>
        <translation>右へ 移動</translation>
    </message>
    <message>
        <location filename="../src/DigitizeState/DigitizeStateSelect.cpp" line="38" />
        <source>Move up</source>
        <translation>上へ 移動</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="93" />
        <location filename="../src/Document/Document.cpp" line="133" />
        <source>Operating system says file is not readable</source>
        <translation>この オペレーティング システム（OS） で読み込みできるファイルタイプではないようです。</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="119" />
        <source>cannot read newer files from version</source>
        <translation>この バージョン のファイル からは 新規読み込みができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="121" />
        <source>of</source>
        <translation>この</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="140" />
        <location filename="../src/util/Xml.cpp" line="40" />
        <source>File</source>
        <translation>ファイル</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="142" />
        <source>was not found</source>
        <translation>見つかりませんでした。</translation>
    </message>
    <message>
        <location filename="../src/Document/Document.cpp" line="511" />
        <source>Cannot read image data</source>
        <translation>画像を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelAxesChecker.cpp" line="96" />
        <source>Cannot read axes checker data</source>
        <translation>座標軸 チェッカー の 情報 を読みこむことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelColorFilter.cpp" line="205" />
        <source>Cannot read filter data</source>
        <translation>フィルター 情報 を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelCoords.cpp" line="172" />
        <source>Cannot read coordinates data</source>
        <translation>座標系 情報 を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelDigitizeCurve.cpp" line="108" />
        <source>Cannot read digitize curve data</source>
        <translation>デジタイズ された カーブ の 情報 を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelExportFormat.cpp" line="203" />
        <source>Cannot read export data</source>
        <translation>エクスポート 情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelGeneral.cpp" line="93" />
        <source>Cannot read general data</source>
        <translation>一般情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelGridDisplay.cpp" line="155" />
        <source>Cannot read grid display data</source>
        <translation>グリッド 表示情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelGridRemoval.cpp" line="191" />
        <source>Cannot read grid removal data</source>
        <translation>グリッド 消去情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelPointMatch.cpp" line="87" />
        <source>Cannot read point match data</source>
        <translation>ポイント マッチング 情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Document/DocumentModelSegments.cpp" line="91" />
        <source>Cannot read segment data</source>
        <translation>セグメント 情報を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportDelimiter.cpp" line="14" />
        <source>Commas</source>
        <translation>コンマ</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportDelimiter.cpp" line="17" />
        <source>Semicolons</source>
        <translation>セミコロン</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportDelimiter.cpp" line="20" />
        <source>Spaces</source>
        <translation>空白文字</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportDelimiter.cpp" line="23" />
        <source>Tabs</source>
        <translation>タブ</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportHeader.cpp" line="14" />
        <source>Gnuplot</source>
        <translation>Gnuplot</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportHeader.cpp" line="17" />
        <source>None</source>
        <translation>なし</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportHeader.cpp" line="20" />
        <source>Simple</source>
        <translation>簡易</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportImageForRegression.cpp" line="26" />
        <source>Export Image</source>
        <translation>画像を エクスポート</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportImageForRegression.cpp" line="27" />
        <source>Cannot export file</source>
        <translation>ファイル を エクスポート することができません。</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportLayoutFunctions.cpp" line="14" />
        <source>AllPerLine</source>
        <translation>全ての カーブ データ を 出力ファイルの各行に並べて表示します。</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportLayoutFunctions.cpp" line="17" />
        <source>OnePerLine</source>
        <translation>出力される データ は カーブ ごとに 分けて表示されます。</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsIntervalUnits.cpp" line="14" />
        <source>Graph Units</source>
        <translation>グラフ の単位</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsIntervalUnits.cpp" line="17" />
        <source>Pixels</source>
        <translation>ピクセル</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsSelectionFunctions.cpp" line="14" />
        <source>InterpolateAllCurves</source>
        <translation>全て の カーブ の X 座標について対応する Y 座標を取得</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsSelectionFunctions.cpp" line="17" />
        <source>InterpolateFirstCurve</source>
        <translation>最初の カーブ の X 座標のみを利用して対応する Y 座標を取得</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsSelectionFunctions.cpp" line="20" />
        <source>InterpolatePeriodic</source>
        <translation>等間隔に X 座標を指定して 対応する Y 座標を取得</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsSelectionFunctions.cpp" line="23" />
        <location filename="../src/Export/ExportPointsSelectionRelations.cpp" line="17" />
        <source>Raw</source>
        <translation>元のデータ</translation>
    </message>
    <message>
        <location filename="../src/Export/ExportPointsSelectionRelations.cpp" line="14" />
        <source>Interpolate</source>
        <translation>補間</translation>
    </message>
    <message>
        <location filename="../src/FileCmd/FileCmdScript.cpp" line="31" />
        <source>Cannot read script file</source>
        <translation>スクリプト ファイル を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/FileCmd/FileCmdScript.cpp" line="33" />
        <source>from directory</source>
        <translation>指定のディレクトリから</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="26" />
        <source>CurveName:</source>
        <translation>カーブ 名</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="27" />
        <source>FunctionArea:</source>
        <translation>補間範囲</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="28" />
        <source>PolygonArea:</source>
        <translation>図形の範囲</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="29" />
        <location filename="../src/Point/PointShape.cpp" line="29" />
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="30" />
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="31" />
        <source>Index</source>
        <translation>インデックス</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="32" />
        <source>Distance</source>
        <translation>距離</translation>
    </message>
    <message>
        <location filename="../src/Geometry/GeometryWindow.cpp" line="33" />
        <source>Percent</source>
        <translation>パーセント</translation>
    </message>
    <message>
        <location filename="../src/Grid/GridCoordDisable.cpp" line="14" />
        <source>Count</source>
        <translation>個数</translation>
    </message>
    <message>
        <location filename="../src/Grid/GridCoordDisable.cpp" line="17" />
        <source>Start</source>
        <translation>開始位置</translation>
    </message>
    <message>
        <location filename="../src/Grid/GridCoordDisable.cpp" line="20" />
        <source>Step</source>
        <translation>間隔</translation>
    </message>
    <message>
        <location filename="../src/Grid/GridCoordDisable.cpp" line="23" />
        <source>Stop</source>
        <translation>終了位置</translation>
    </message>
    <message>
        <location filename="../src/Grid/GridLineFactory.cpp" line="67" />
        <source>Axes checker. If this does not align with the axes, then the axes points should be checked</source>
        <translation>座標軸 チェッカー の表示が 座標軸と一致するかどうかを確認し、一致が見られない場合には 基準とした ポイント を再確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Import/ImportCroppingUtilBase.cpp" line="22" />
        <source>No cropping</source>
        <translation>切り抜きをしない</translation>
    </message>
    <message>
        <location filename="../src/Import/ImportCroppingUtilBase.cpp" line="23" />
        <source>Crop pdf files with multiple pages</source>
        <translation>複数の ページ に亘る PDF ファイル の一部を切り抜きます。</translation>
    </message>
    <message>
        <location filename="../src/Import/ImportCroppingUtilBase.cpp" line="24" />
        <source>Always crop</source>
        <translation>常に切り抜きを実行</translation>
    </message>
    <message>
        <location filename="../src/Line/LineStyle.cpp" line="124" />
        <source>Cannot read line style data</source>
        <translation>ライン の スタイル 設定を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Point/Point.cpp" line="370" />
        <source>Cannot read point data</source>
        <translation>ポイント の データ を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/Point/PointIdentifiers.cpp" line="87" />
        <source>Cannot read point identifiers</source>
        <translation>ポイント を認識 することができません。</translation>
    </message>
    <message>
        <location filename="../src/Point/PointShape.cpp" line="14" />
        <source>Circle</source>
        <translation>円形</translation>
    </message>
    <message>
        <location filename="../src/Point/PointShape.cpp" line="17" />
        <source>Cross</source>
        <translation>十字</translation>
    </message>
    <message>
        <location filename="../src/Point/PointShape.cpp" line="20" />
        <source>Diamond</source>
        <translation>ひし形</translation>
    </message>
    <message>
        <location filename="../src/Point/PointShape.cpp" line="23" />
        <source>Square</source>
        <translation>正方形</translation>
    </message>
    <message>
        <location filename="../src/Point/PointShape.cpp" line="26" />
        <source>Triangle</source>
        <translation>三角形</translation>
    </message>
    <message>
        <location filename="../src/Point/PointStyle.cpp" line="146" />
        <source>Cannot read point style data</source>
        <translation>ポイント の スタイル 設定を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="20" />
        <source>Coordinates (pixels):</source>
        <translation>ピクセル単位の座標</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="21" />
        <source>Coordinates (graph):</source>
        <translation>グラフ座標の座標</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="22" />
        <source>Resolution (graph):</source>
        <translation>グラフ座標における解像度</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="11" />
        <source>16:1 farther</source>
        <translation>16:1 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="12" />
        <source>8:1 closer</source>
        <translation>8:1 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="14" />
        <source>8:1 farther</source>
        <translation>8:1 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="15" />
        <source>4:1 closer</source>
        <translation>4:1 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="17" />
        <source>4:1 farther</source>
        <translation>4:1 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="18" />
        <source>2:1 closer</source>
        <translation>2:1 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="20" />
        <source>2:1 farther</source>
        <translation>2:1 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="21" />
        <source>1:1 closer</source>
        <translation>1:1 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="23" />
        <source>1:1 farther</source>
        <translation>1:1 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="24" />
        <source>1:2 closer</source>
        <translation>1:2 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="26" />
        <source>1:2 farther</source>
        <translation>1:2 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="27" />
        <source>1:4 closer</source>
        <translation>1:4 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="29" />
        <source>1:4 farther</source>
        <translation>1:4 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="30" />
        <source>1:8 closer</source>
        <translation>1:8 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="32" />
        <source>1:8 farther</source>
        <translation>1:8 よりやや遠望</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="33" />
        <source>1:16 closer</source>
        <translation>1:16 よりやや近接</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="35" />
        <source>Fill</source>
        <translation>フィル</translation>
    </message>
    <message>
        <location filename="../src/Zoom/ZoomLabels.cpp" line="36" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="3683" />
        <source>Need scale bar</source>
        <translation>スケールバー が必要です。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindow.cpp" line="3684" />
        <source>Need more axis points</source>
        <translation>座標軸の基準となる点がさらに必要です。</translation>
    </message>
    <message>
        <location filename="../src/main/MainWindowModel.cpp" line="105" />
        <source>Cannot read main window data</source>
        <translation>メイン画面 の設定を読み込むことができません。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="229" />
        <source>Enables extra debug information. Used for debugging</source>
        <translation>エラー 解決のため追加情報を表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="231" />
        <source>Specifies an error report file as input. Used for debugging and testing</source>
        <translation>エラー レポート の ファイル を設定します。エラー 処理や テスト の際に使用します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="233" />
        <source>Specifies a file command script file as input. Used for debugging and testing</source>
        <translation>コマンド の スクリプト ファイル を設定します。エラー 処理や テスト の際に使用します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="235" />
        <source>Output diagnostic gnuplot input files. Used for debugging</source>
        <translation>gnuplot 用の入力ファイルを問題確認の可能な形で出力し エラー処理に使用します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="237" />
        <source>Show this help information</source>
        <translation>ヘルプ　を表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="239" />
        <source>Executes the error report file or file command script. Used for regression testing</source>
        <translation>エラー レポート あるいは コマンド スクリプト を ファイル として出力します。これらは リグレッション テスト に使用されます。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="241" />
        <source>Removes all stored settings, including window positions. Used when windows start up offscreen</source>
        <translation>全ての 設定条件を クリア します。これにはこの ソフト の画面位置の情報も含まれるので、 起動時にこの ソフト が コンピューター 画面の外に表示されるような場合に対処可能になります。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="243" />
        <source>Show a list of available styles that can be used with the -style command</source>
        <translation>いくつかの 設定条件のなかで -style コマンド で利用可能なものを リスト として表示します。</translation>
    </message>
    <message>
        <location filename="../src/main/main.cpp" line="245" />
        <source>File(s) to be imported or opened at startup</source>
        <translation>ソフト の開始時点で開く ファイル (複数可)</translation>
    </message>
    <message>
        <location filename="../src/util/Xml.cpp" line="34" />
        <source>Start at line</source>
        <translation>開始位置</translation>
    </message>
    <message>
        <location filename="../src/util/Xml.cpp" line="42" />
        <source>at line</source>
        <translation>ライン 位置</translation>
    </message>
    <message>
        <location filename="../src/util/Xml.cpp" line="51" />
        <source>Quitting</source>
        <translation>終了しています。</translation>
    </message>
    <message>
        <location filename="../src/util/Xml.cpp" line="54" />
        <source>Error reading xml</source>
        <translation>xml を読み込む際に エラー が発生しました。</translation>
    </message>
</context>
<context>
    <name>StatusBar</name>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="63" />
        <source>Select cursor coordinate values to display.</source>
        <translation>表示する カーソル 座標を選択</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="64" />
        <source>Select Cursor Coordinate Values

Values at cursor coordinates to display. Coordinates are in screen (pixels) or graph units. Resolution (which is the number of graph units per pixel) is in graph units. Graph units are only available after axis points have been defined.</source>
        <translation>カーソル 座標値の表示選択

カーソル 位置 での座標値として表示する値を設定します。座標は コンピューター画面の ピクセル (数) あるいは グラフ 上での単位のいずれでも示すことが可能です。精度 は (つまり 一つのピクセルの サイズ ) は グラフ 単位 で示されます。 グラフ の単位 での表示は 座標軸 の基準となる ポイント の設定が終わっていないと選択できません。</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="77" />
        <source>Cursor coordinate values.</source>
        <translation>カーソル 位置 の座標値</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="78" />
        <source>Cursor Coordinate Values

Values at cursor coordinates. Coordinates are in screen (pixels) or graph units. Resolution (which is the number of graph units per pixel) is in graph units. Graph units are only available after axis points have been defined.</source>
        <translation>カーソル 位置の座標値

カーソル 位置 の座標値を示します。座標は コンピューター 画面のピクセル  (数) またはグラフ 上での単位のいずれでも示すことが可能です。精度は (つまり一つのピクセルのサイズは) グラフ の単位で示されます。グラフ の 単位での表示は座標軸の基準となる ポイント の設定が終わっていないと選択できません。</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="132" />
        <source>Select zoom.</source>
        <translation>拡大縮小 率を設定</translation>
    </message>
    <message>
        <location filename="../src/StatusBar/StatusBar.cpp" line="133" />
        <source>Select Zoom

Points can be more accurately placed by zooming in.</source>
        <translation>拡大縮小率を設定

拡大率を上げることで ポイント 位置をより精確に定めることができます。</translation>
    </message>
</context>
<context>
    <name>TutorialStateAxisPoints</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="26" />
        <source>Axis Points</source>
        <translation>座標軸の基準となるポイント</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="29" />
        <source>Axis points are first defined to
define the coordinates. Step 1 -
Click on the Axis Points button</source>
        <translation>座標軸を定めるため、まず基準となる ポイント を設定します。
ステップ1 - 座標軸の基準ポイント ボタン を押します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="33" />
        <source>Step 2 - Click on an axis or grid
line with known coordinates. An axis
point appears, with a dialog window
for entering the axis point's
coordinates</source>
        <translation>ステップ 2 - 座標軸または グリッド の線上で座標値の分かっている位置をクリックします。
その点は座標軸 の基準となる ポイント として表示され、 またそれらのポイント の座標入力を促すダイアログ画面が現れます。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="39" />
        <source>Step 3 - Enter the two coordinates
of the axis point and then click Ok.
Repeat steps 2 and 3 twice more
until three axis points are created</source>
        <translation>ステップ 3 - 座標を示す 2つの値を入力してOkをクリックします。
この ステップ 2 と 3 をさらに2 回繰り返して、基準となる3つのポイント全てを指定します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="47" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateAxisPoints.cpp" line="53" />
        <source>Next</source>
        <translation>次へ</translation>
    </message>
</context>
<context>
    <name>TutorialStateChecklistWizardAbstract</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="26" />
        <source>Checklist Wizard and Checklist Guide</source>
        <translation>チェックリスト ウィザード と手引き</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="29" />
        <source>For new Engauge users, a Checklist Wizard
is available when importing an image file.
This wizard produces a helpful checklist of
steps to follow to digitize the image file.</source>
        <translation>新たに Engauge を使い始めた ユーザー 向けに、画像ファイルの インポート に応じて チェックリスト ウィザード が利用できるようになっています。
この ウィザード は、画像のデジザイズ に必要な 手順を進めるための チェックリスト として有用です。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="34" />
        <source>Step 1 - Enable the menu option Help /
Checklist Guide Wizard.</source>
        <translation>ステップ 1 - ヘルプ メニュー を開きます。 
チェックリスト と 手引き ウィザード にチェック を入れて有効にしてください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="37" />
        <source>Step 2 - Import the file using File /
Import. The Checklist Wizard will appear
and ask some simple questions to
determine how the image can be
digitized.</source>
        <translation>ステップ 2 - ファイル メニュー の インポート から、画像ファイルをインポート します。
すると チェックリスト と 手引き ウィザード 画面が表示されますので、簡単な質問に答えながら画像を デジタイズ するための手順を確認してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="43" />
        <source>Additional options are available in
the various Settings menus.

This ends the tutorial. Good luck!</source>
        <translation>他にもいくつかの オプション を 設定 メニュー で指定することができますよ。
Good luck!</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateChecklistWizardAbstract.cpp" line="50" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
</context>
<context>
    <name>TutorialStateColorFilter</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="26" />
        <source>Color Filter</source>
        <translation>カラー フィルター</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="29" />
        <source>Each curve has Color Filter settings that
are applied in Segment Fill mode. For
black lines the defaults work well, but for
colored lines the settings can be improved.</source>
        <translation>セグメント フィル モード では それぞれの カーブ について、カラー フィルター 設定を行うことができます。
画像の ライン の色が黒である場合には デフォルト の設定で十分ですが、カラー 画像を扱う場合には、この設定を調整して精度を上げてください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="34" />
        <source>Step 1 - Select the Settings / Color
Filter menu option.</source>
        <translation>ステップ 1 - 設定 メニュー から カラー フィルター 設定画面を開きます。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="37" />
        <source>Step 2 - Select the curve that will
be given the new settings.</source>
        <translation>ステップ 2 - 設定を変更したい カーブ を選択してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="40" />
        <source>Step 3 - Select the mode. Intensity is
suggested for uncolored lines, and Hue
is suggested for colored lines.</source>
        <translation>ステップ 3 - フィルター モード を選択します。
一般に、白黒画像の場合には輝度が、 カラー 画像の場合には 色相が、それぞれお勧めです。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="44" />
        <source>Step 4 - Adjust the included range by
dragging the green handles, until the
curve is clear in the preview window
below. The graph shows a histogram
distribution of the values underneath.
Click Ok when finished.</source>
        <translation>ステップ 4 - 右上の ヒストグラム では 緑色のつまみを使って フィルター の範囲を調整できます。
つまみを左右に動かして、下の プレビュー 画面で カーブ が明瞭に見えるようにしてください。
なお、この ヒストグラム は そのすぐ下に帯状の画像として表示されている 色分布に対応しています。
調整が終わりましたら Ok ボタンを押してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateColorFilter.cpp" line="54" />
        <source>Back</source>
        <translation>戻る</translation>
    </message>
</context>
<context>
    <name>TutorialStateCurveSelection</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="29" />
        <source>After the axis points have been created, a
curve is selected to receive curve points.
Step 1 - click on Curve, Point Match, Color
Picker or Segment Fill buttons.</source>
        <translation>座標軸 の基準となる ポイント の設定が終わったら、 カーブ が デジタイズ できるようになります。
ステップ 1 - カーブ ・ ポイント マッチ ・ カラーピッカー ・セグメント フィル のいずれかの ボタン をクリック します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="34" />
        <source>Step 2 - Select the desired curve name. If
that curve name has not been created yet,
use the menu option Settings / Curve Names
to create it.</source>
        <translation>ステップ 2 - 対象とする カーブ 名を選択します。
もしその カーブ 名がまだないようでしたら、設定 メニュー から カーブ の追加と削除 画面を開いて新規に作成してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="39" />
        <source>Step 3 - Change the background from the
original image to the filtered image
produced for the current curve, using the
menu option View / Background / Filtered
Image. This filtering enables the powerful
automated algorithms discussed later in
the tutorial.</source>
        <translation>ステップ 3 - バックグラウンド 画像を 元の 画像から 現在の カーブ 用にフィルタ 処理の済んだ画像に変更します。
メニュー からは ビュー / バックグラウンド / フィルタ 画像 を選択します。
フィルタ 画像を利用することで、強力な自動認識 アルゴリズム を適用できるようになります。この アルゴリズム については この チュートリアル に別途詳しい説明があります。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="47" />
        <source>If the current curve is no longer visible
in the filtered image, then change the
current Color Filter settings. In the figure,
the orange points have disappeared.</source>
        <translation>もし 選択中の カーブ が バックグラウンド の フィルター画像 では見えないあるいは見えにくいようであれば、 カラーフィルター 設定を変更してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="55" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="61" />
        <source>Color Filter Settings</source>
        <translation>カラーフィルター 設定</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveSelection.cpp" line="67" />
        <source>Next</source>
        <translation>次へ</translation>
    </message>
</context>
<context>
    <name>TutorialStateCurveType</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="26" />
        <source>Curve Type</source>
        <translation>カーブ の種類</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="29" />
        <source>The next steps depend on how the curves
are drawn, in terms of lines and points.</source>
        <translation>次の ステップ は、対象の カーブ が ポイント なのか ライン なのかに応じて選択してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="32" />
        <source>If the curves are drawn
with lines (with or without
points) then click on
Next (Lines).</source>
        <translation>もし対象の カーブ が ライン であるとき ( ポイント を伴う場合も含めて) 、ライン (ポイントも含む) を選択して 次へ をクリックしてください。 </translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="37" />
        <source>If the curves are drawn
without lines and only
with points, then click on
Next (Points).</source>
        <translation>もし対象の カーブが ポイント だけで構成されており、ライン を含まない場合には、ポイントのみ (ライン なし) を選択して 次へ をクリックしてください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="45" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="51" />
        <source>Next (Lines)</source>
        <translation>次へ </translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateCurveType.cpp" line="57" />
        <source>Next (Points)</source>
        <translation>次へ</translation>
    </message>
</context>
<context>
    <name>TutorialStateIntroduction</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateIntroduction.cpp" line="26" />
        <source>Introduction</source>
        <translation>イントロダクション</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateIntroduction.cpp" line="29" />
        <source>Engauge Digitizer starts with
images of graphs and maps.</source>
        <translation>Engauge Digitizer は、まず グラフ や マップ の画像を インポート するところから作業を開始します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateIntroduction.cpp" line="32" />
        <source>You create (or digitize) points along
the graph and map curves.</source>
        <translation>ここでの デジタイズ 作業は グラフ や マップ の カーブ に沿って ポイント を 打つ (デジタイズ する) ことを指します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateIntroduction.cpp" line="35" />
        <source>The digitized curve points can be
exported, as numbers, to other software tools.</source>
        <translation>デジタイズ された カーブ の ポイント は 数値として 他の ソフトウェア で利用できるよう、 エクスポート することが可能です。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateIntroduction.cpp" line="41" />
        <source>Next</source>
        <translation>次へ</translation>
    </message>
</context>
<context>
    <name>TutorialStatePointMatch</name>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="26" />
        <source>Point Match</source>
        <translation>ポイント マッチング</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="29" />
        <source>In Point Match mode, you pick
one sample point, and Engauge
then finds all matching points.

Step 1 - Click on Point Match mode.</source>
        <translation>ポイント マッチング モード では、サンプル となる ポイント を指定してください。 すると Engauge が自動的に マッチング する ポイント を認識します。

ステップ 1 - ポイント マッチング モード ボタン を クリック してください。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="34" />
        <source>Step 2 - Select the curve the new
points will belong to.</source>
        <translation>ステップ 2 - 対象の カーブ を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="37" />
        <source>Step 3 - Click on a typical point.
The circle turns green when it
contains what may be a point.</source>
        <translation>ステップ 3 - 代表的な ポイント を クリック します。
このとき、 ポイント として認識される可能性のあるところに マウス カーソル を合わせると、カーソル を囲む円の色が 緑色に変化します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="41" />
        <source>Step 4 - Engauge will show a
matched point with a yellow cross.
Press the Right Arrow key to accept
the matched point. Repeat this step
until there are no more points.</source>
        <translation>ステップ 4 - Engauge が マッチング したと認識したところに 黄色い十字が表示されます。この ポイント で良ければ、マウス で クリック するか、キーボード 上の 右矢印 キー を押して確定してください。
この作業を全てのポイントについて繰り返します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="50" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStatePointMatch.cpp" line="56" />
        <source>Next</source>
        <translation>次へ</translation>
    </message>
</context>
<context>
    <name>TutorialStateSegmentFill</name>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="26" />
        <source>Segment Fill</source>
        <translation>セグメント フィル</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="29" />
        <source>Segment Fill mode places several
points all along the line segments
of a curve. Step 1 - Click on the
Segment Fill button.</source>
        <translation>セグメント フィル モード では、対象の カーブ について、線分に沿っていくつかの ポイント を追加します。
ステップ 1 - セグメント フィル ボタン をクリックします。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="34" />
        <source>Step 2 - Select the curve the new
points will belong to.</source>
        <translation>ステップ 2 - 対象の カーブ を選択します。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="37" />
        <source>Step 3 - Move the cursor over a line
segment in the desired curve. If a
green line appears, click on it once
to generate many points.</source>
        <translation>ステップ 3 - カーブ 選択後、マウス カーソル を 移動 させ、画像の線分に合わせてください。
もし緑色の線が対象の線分に沿って正しく表示されたら、そこで マウス をクリックします。
多くの ポイント が一度に生成されるはずです。</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="45" />
        <source>Previous</source>
        <translation>前へ</translation>
    </message>
    <message>
        <location filename="../src/Tutorial/TutorialStateSegmentFill.cpp" line="51" />
        <source>Next</source>
        <translation>次へ</translation>
    </message>
</context>
</TS>