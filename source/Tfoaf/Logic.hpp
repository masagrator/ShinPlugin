#pragma once

#include "Tree.hpp"

namespace SH1 {
	ptrdiff_t LogicOffset = 0x16810;

	std::array Logic_data = {
		//Index 0
		Text{"田村光太郎（たむら・こうたろう）", "Tamura Koutarou"},
		Text{"両目を鋏で貫かれ殺害された。", "Murdered. Scissors were used to gouge his eyes."},
		Text{"水瀬遥（みなせ・はるか）", "Minase Haruka"},
		Text{"牧村早苗（まきむら・さなえ）", "Makimura Sanae"},
		Text{"Ｃ村で起きていた多数の行方不明事件、", "Missing Persons cases have been reported in Town C."},
		Text{"Ｃ村の福祉施設の理事長。", "Chairman of the Welfare facility in Town C."},
		Text{"砂堀優子（すなほり・ゆうこ）", "Sunahori Yuuko"},
		Text{"砂堀将春（すなほり・まさはる）", "Sunahori Masaharu"},
		Text{"砂堀聡史（すなほり・さとし）", "Sunahori Satoshi"},
		Text{"黒田邦雄（くろだ・くにお）", "Kuroda Kunio"},
		Text{"風守隼人（かざもり・はやと）", "Kazamori Hayato"},
		Text{"思った事がすぐ口に出てしまう。", "Can't help but think out loud."},
		Text{"立花美鈴（たちばな・みすず）", "Tachibana Misuzu"},
		Text{"ブラインドマン", "Blind Man"},
		Text{"関本爽二朗（せきもと・そうじろう）", "Sekimoto Soujirou"},
		Text{"津田沼陽一（つだぬま・よういち）", "Tsudanuma Youichi"},
		Text{"金谷大夢（かなや・ひろむ）","Kanaya Hiromu"},
		Text{"どの捜査現場にも野次馬をしている。", "A Wild Card"},
		Text{"竹中慎一郎（たけなか・しんいちろう）", "Takenaka Shinichirou"},
		Text{"現在の職業は不詳。", "Ocupation Unknown"},
		Text{"竹中浩三（たけなか・こうぞう）", "Takenaka Kouzou"},
		Text{"竹中千鶴子（たけなか・ちづこ）", "Takenaka Chizuko"},
		Text{"亘胡桃（わたり・くるみ）", "Watari Kuromi"},
		Text{"いつも笑みを絶やさないのが魅力でもあり怖さでもある。", "Constantly smiling. Is both charming yet scary."},
		Text{"生活費を稼ぐために夜のお店で働いているらしい。", "Work's a night club to make ends meet."},
		Text{"遥さんと接点があり、田村さんと自分の家族の殺害を供述。", "Had a connection with Haruka. Stated they killed Tamura and their own family."},

		Text{"空欄のまま保留", "Blank, Pending Investigation"},
		Text{"関本は模範囚だ", "Sekimoto is a model prisoner."},
		Text{"関本はインテリだ", "Sekimoto is an academic."},
		Text{"関本はナンパ野郎だ", "Sekimoto is a pick-up artist."},
		Text{"関本はコメディアンだ", "Sekimoto is a comedian."},
		Text{"関本はペテン師だ", "Sekimoto is a phony."},
		Text{"関本はイカれた殺人鬼だ", "Sekimoto is a psychopath."},
		Text{"関本は地下牢の悪魔だ", "Sekimoto is the Devil in the Dungeon."},

		Text{"空欄のまま保留た牧師だ", "Blank, Pending Investigation."},
		Text{"ブラインドマンの正体は私だ", "The Blind Man's true identity is Me."},
		Text{"ブラインドマンの正体は風守さんだ", "The Blind Man's true identity is Kazamori"},
		Text{"ブラインドマンの正体は黒田課長だ", "The Blind Man's true identity is Kuroda"},
		Text{"ブラインドマンの正体は関本だ", "The Blind Man's true identity is Sekimoto"},
		Text{"ブラインドマンの正体は美鈴だ", "The Blind Man's true identity is Tachibana"},
		Text{"ブラインドマンの正体は遥さんだ", "The Blind Man's true identity is Haruka"},
		Text{"ブラインドマンの正体は砂堀さんだ", "The Blind Man's true identity is Sunahori"},
		Text{"ブラインドマンの正体は優子さんだ", "The Blind Man's true identity is Yuuko"},
		Text{"ブラインドマンの正体は聡史くんだ", "The Blind Man's true identity is Satoshi"},
		Text{"ブラインドマンの正体は早苗さんだ", "The Blind Man's true identity is Sanae"},
		Text{"ブラインドマンの正体は津田沼さんだ", "The Blind Man's true identity is Tsudanuma"},
		Text{"ブラインドマンの正体は竹中慎一郎だ", "The Blind Man's true identity is Takenaka.S"},
		Text{"ブラインドマンの正体は亘さんだだ", "The Blind Man's true identity is Watari"},

		Text{"空欄のまま保留正体は金谷大夢だ", "Blank, Pending Investigation."},
		Text{"遥さんと田村さんは友人関係だった", "Haruka and Tamura were best friends."},
		Text{"遥さんと田村さんは恋人同士だった", "Haruka and Tamura were lovers."},
		Text{"遥さんは田村さんにＤＶを受けていた", "Haruka was subjected to domestic violence by Tamura."},
		Text{"遥さんの青あざは田村さんによるものだ", "Haruka's bruising is caused by Tamura."},
		Text{"遥さんは田村さんに復讐をしたものだ", "Haruka was the one who took revenge on Tamura."},
		Text{"遥さんは田村さんに怨恨があった", "Haruka had a grudge against Tamura."},

		Text{"空欄のまま保留の愛人だったのだ", "Blank, Pending Investigation."},
		Text{"田村さんは砂堀さんに貸し剥がしをした", "Tamura stripped Sunahori of his debt."},
		Text{"砂堀さんは田村さんに殴り込みに行った", "Sunahori went to confront Tamura."},
		Text{"砂堀さんは田村さんに土下座した", "Sunahori got down on his knees to Tamura."},
		Text{"砂堀さんは田村さんに怨恨があった", "砂堀さんは田村さんに怨恨があった"},

		Text{"空欄のまま保留んに怨恨があったた", "Blank, Pending Investigation."},
		Text{"牧村さんは田村さんに怨恨があった", "Makimura had a grudge against Tamura."},
		Text{"牧村さんは田村さんと面識がなかった", "Makimura had never met Tamura."},
		Text{"牧村さんは田村さんの保険金が目的だった", "牧村さんは田村さんの保険金が目的だった"},

		Text{"空欄のまま保留んの保険金が目的だった", "Blank, Pending Investigation."},
		Text{"津田沼さんはスクープを欲しがっている", "Tsudanuma wants the scoop."},
		Text{"津田沼さんはジャーナリズムを大切にしている",  "Tsudanuma values journalism."},

		Text{"空欄のまま保留ポーズをするつもりだいる", "Blank, Pending Investigation."},
		Text{"金谷大夢は善良な市民だするつもりだいる", "Kanaya Hiromu is a good citizen."},
		Text{"金谷大夢は偉大なる小説家だつもりだいる", "Kanaya Hiromu is a great novelist."},
		Text{"金谷大夢の正体は餓鬼だったつもりだいる", "Kanaya Hiromu is a Brat."},

		Text{"空欄のまま保留毒者だったつもりだいる", "空欄のまま保留毒者だったつもりだいる"},
		Text{"遥さんと金谷大夢は共犯だったもりだいる", "遥さんと金谷大夢は共犯だったもりだいる"},
		Text{"遥さんにとって金谷大夢は都合のいい客だった", "遥さんにとって金谷大夢は都合のいい客だった"},
		Text{"遥さんは金谷大夢から札束を受け取っていた", "遥さんは金谷大夢から札束を受け取っていた"},
		Text{"遥さんは汚物処理担当として金谷大夢に接していた", "遥さんは汚物処理担当として金谷大夢に接していた"},

		Text{"空欄のまま保留にダイエット薬品を渡していた", "Blank, Pending Investigation."},
		Text{"ブラインドマンと金谷大夢は共犯だったていた", "The Blind Man & Kanaya are accomplices."},
		Text{"ブラインドマンは金谷大夢にダイエット薬品を渡していた", "The Blind Man was giving Kanaya the Diet Pills."},
		Text{"ブラインドマンは金谷大夢を身代わりにさせたしていた", "The Blind Man had Kanaya take his place."}
	};
	std::span<Text> Logic(Logic_data);
}