#pragma once

#include <vector>

struct Text {
    std::string JPN;
    std::string ENG;
};


std::vector<ptrdiff_t> TreeOffsets = {
    0x31cec, //0x2C
    0x31ed0, //0x4C
    0x31f2c, //0x8C
    0x31f8c, //0xCC
    0x32090  //0x2C
};

std::vector<Text> Tree2C = {
    {"譲歩", "譲歩"},
    {"オープニング", "Opening"},
    {"証言台にて", "Witness Stand"},
    {"逮捕の瞬間", "Captured"},
    {"涼しい横顔", "Composed"},
    {"選択肢", "Choices"},
    {"疑問への回答", "Answers"},
    {"煽った代償", "Price of Aggravation"},
    {"東拘", "Tokyo Detention"},
    {"交換条件", "Bargaining"},
    {"檻の中", "Caged"},
    {"選択肢", "Choices"},
    {"皮肉", "Satire"},
    {"叱責", "Scold"},
    {"事件概要", "Summary"},
    {"言葉の牙", "Harsh Words"},
    {"関本の本心を探れ！", "What Sekimoto is really thinking"},
    {"選択肢", "Choices"},
    {"仲裁", "Arbitration"},
    {"ガイシャの正体", "Victims Identity"},
    {"選択肢", "Choices"},
    {"立花美鈴と関本爽二朗", "Misuzu & Soujiro"},
    {"判断", "Judgment"},
    {"興味", "Interest"},
    {"今後の方針", "Future Plan"},
    {"女子大生", "Uni Student"},
    {"選択肢", "Choices"},
    {"刑事告訴もの", "Criminal Complaint?"},
    {"リベンジ", "Revenge"},
    {"彼女のアリバイ", "Her Alibi"},
    {"砂堀酒造", "Brewery"},
    {"選択肢", "Choices"},
    {"激昂", "Indignation"},
    {"突発的な行動", "Spontaneous"},
    {"引き取り", "Acceptance"},
    {"閑話休題", "Digression"},
    {"福祉学生", "Welfare Student"},
    {"人物関係", "Personal Feelings"},
    {"選択肢", "Choices"},
    {"完黙再び", "Silence"},
    {"選択肢", "Choices"},
    {"選択肢", "Choices"},
    {"選択肢", "Choices"},
    {"取材記者", "Legman"},
    {"狐と狸の応酬", "Fox & Tanuki's Exchange"},
    {"津田沼を上手くコントロールせよ！", "Get Tsudanuma under control!"},
    {"週刊サラリー", "Weekly Salary"},
    {"選択肢", "Choices"},
    {"防犯カメラ", "Security Camera"},
    {"取引に乗る", "The Deal"},
    {"断末魔の叫び", "Screaming in Agony"},
    {"選択肢", "Choices"},
    {"方法について", "Methods"},
    {"遺体状況", "Corpse Status"},
    {"歯", "Teeth"},
    {"現場記録", "Field Notes"},
    {"金谷大夢", "Kanaya Hiromu"},
    {"恫喝", "Intimidation"},
    {"屁理屈屋の金谷を屈服させろ！", "Bring Kanaya to his knees!"},
    {"生命の危機", "Life-Threatening"},
    {"多汗症", "Hyperhidrosis"},
    {"張り込み", "Steakout"},
    {"選択肢", "Choices"},
    {"緊急対応", "Emergency Response"},
    {"増援要請", "Request for Back-up"},
    {"状況確認", "Checking the Situation"},
    {"突入", "Storming"},
    {"妖怪", "Yokai"},
    {"選択肢", "Choices"},
    {"先輩の勇気", "Senior Courage"},
    {"正直な心境", "Honest Feelings"},
    {"異様", "Odd"},
    {"山狩り", "Mountain Hunt"},
    {"たった二人の捜査班", "Two Investigators"},
    {"選択肢", "Choices"},
    {"ねめつける視線", "Glare"},
    {"五月蠅い呼吸", "Labored Breath"},
    {"かぶりつき", "Front-row Seats"},
    {"餓鬼", "Preta"},
    {"犯人確保", "Secure Prisoner"},
    {"水瀬との関係", "Relationship With Minase"},
    {"選択肢", "Choices"},
    {"歓喜", "Delight"},
    {"驚愕", "Shock"},
    {"畏怖", "Awe"},
    {"三文芝居", "Three Sentence Play"},
    {"選択肢", "Choices"},
    {"志願", "Desire"},
    {"仇討ち", "Vengeance"},
    {"過小評価", "Underestimation"},
    {"四度目の正直", "Fourth Time's the Charm"},
    {"事情聴取", "Interrogation"},
    {"金谷の心の中", "Inside Kanaya's Mind"},
    {"水瀬になりきって聴取せよ！", "Listen like you're Minase!"},
    {"憔悴の気持ち", "Exhaustion"},
    {"打ち切り", "Cancellation"},
    {"選択肢", "Choices"},
    {"悪あがき", "Useless Resistance"},
    {"悔しくて", "Annoyed"},
    {"薬物", "Medicines"},
    {"送還へ", "Deportation"},
    {"通達", "Directive"},
    {"護送", "Escort"},
    {"選択肢", "Choices"},
    {"救急車", "Ambulance"},
    {"緊急事態", "State of Emergency"},
    {"救護方法", "Relief"},
    {"バイタルサイン", "Vital Signs"},
    {"応援要請状況", "Request for Support"},
    {"拉致", "Kidnapping"},
    {"選択肢", "Choices"},
    {"笑顔", "Smiling"},
    {"理解不能の怖さ", "Scary Beyond Comprehension"},
    {"理解不能の感情", "Feelings I Don't Understand"},
    {"脱出へ", "Escape"},
    {"処理部屋", "Treatment Room"},
    {"選択肢", "Choices"},
    {"水瀬遥殺人事件", "Minase Haruka Murder Case"},
    {"ブラインドマン", "Blind Man"},
    {"連続殺人事件", "Serial Murders"},
    {"クイズの正解", "Quiz"},
    {"推理ロジック", "Inference Logic"},
    {"失敗", "Mistake"},
    {"告白", "Confession"},
    {"命乞い", "Begging for Your Life"},
    {"生きるために言葉で足掻け！", "Fumble your words to stay alive!"},
    {"鏡の中の私", "My Reflection"},
    {"覚悟", "Resolution"},
    {"東拘", "Tokyo Detention"},
    {"選択肢", "Choices"},
    {"急行", "Moving Fast"},
    {"嫌悪感", "Dab Feelings"},
    {"完黙再び", "Silence"},
    {"成就", "Achievements"},
    {"留置所の特別講義", "Special Lecture"},
    {"竹中慎一郎", "Takenaka"},
    {"鑑識の結果", "Forensics Results"},
    {"選択肢", "Choices"},
    {"選択肢", "Choices"},
    {"おどけた後", "After the Joke"},
    {"風守さんはどこへ？", "Where's Kazamori?"},
    {"選択肢", "Choice"},
    {"休憩所には？", "Where's the rest stop?"},
    {"特ラ課オフィスには？", "What's in the Office?"},
    {"まさか、あそこへ？", "You're not going in there, are you?"},
    {"選択肢", "Choices"},
    {"関本の嗅覚", "Sekimoto's Sense of Smell"},
    {"砂堀酒造へ", "To the Sunahori Brewery"},
    {"選択肢", "Choices"},
    {"飲み込んだ言葉", "Swallow My Words"},
    {"では頂きます", "Let's eat"},
    {"心霊写真？", "Ghost photo?"},
    {"選択肢", "Choices"},
    {"妖精事件", "Fairy Incident"},
    {"偶然の映像", "Accidental Video"},
    {"心霊写真講釈", "Ghost photo review"},
    {"接点の女", "Contact"},
    {"水瀬の信用を勝ち取れ！", "Win Minase's trust!"},
    {"水瀬遥の告白", "Minase's Confession"},
    {"閉ざす心", "Closed-minded"},
    {"選択肢", "Choices"},
    {"根気よく待つ", "Waiting patiently"},
    {"疑っていない", "I don't doubt that"},
    {"唐突の来訪", "Sudden Visit"},
    {"水瀬の死", "Death of Minase"},
    {"再び関本に", "Sekimoto, Again"},
    {"水瀬宅へ", "Minase's House"},
    {"アルバムの心霊写真", "Psychic Photo Album"},
    {"不審死製造機", "No Trial"},
    {"風守に意見を聞いて懐柔しろ！", "Ask Kazamori for his oppinion!"},
    {"捜査の決意", "Determination"},
    {"決めるなら？", "Have you decided?"},
    {"選択肢", "Choices"},
    {"やります", "I'll do it"},
    {"やらない", "I won't do it"},
    {"……もう少し", "A little more"},
    {"選択肢", "Choices"},
    {"唐突に襲いかかる", "Suddenly it Hits you"},
    {"３度関本と", "Three Times"},
    {"美鈴にも霊が？", "Misuzu Possessed?"},
    {"選択肢", "Choices"},
    {"何をしたの", "What did you do?"},
    {"見えているの", "I see you"},
    {"どうかしたの", "What's Wrong?"},
    {"覗く何者か", "Looking In"},
    {"美鈴の身辺捜査", "Misuzu's Personal Affairs"},
    {"美鈴の過去", "Misuzu's Past"},
    {"推理ロジック", "Inference Logic"},
    {"死霊の再訪", "Revisiting the Dead"},
    {"美鈴への聴取", "Misuzu's Interview"},
    {"選択肢", "Choices"},
    {"心配なの", "Worried"},
    {"真相を話して", "Tell me the truth"},
    {"立花から真相を引き出せ！", "Get the truth from Tachibana!"},
    {"キューピッドさん", "Cupid"},
    {"ならば感情に", "You're Emotional"},
    {"選択肢", "Choices"},
    {"涙ながらに", "Tears"},
    {"泣き喚いて", "Crying"},
    {"再びのメール", "Email"},
    {"選択肢", "Choices"},
    {"美鈴の最後", "Misuzu's End"},
    {"黒いもやが這う", "Black Mist"},
    {"最後の友達", "My last Friend"},
    {"公務中なので", "Official Business"},
    {"あくまで試供品として", "Just a Sample"},
    {"醤油の匂い", "The smell of Soy Sauce"},
    {"人毛醤油", "Human Hair Soy Sauce"},
    {"選択肢", "Choices"},
    {"面白半分伝説", "Half-interesting legend"},
    {"風評伝説", "Urban Legend Rumors"},
    {"理由を問われて", "Asked Why"},
    {"人体由来の固有", "Human Origin"},
    {"砂堀酒造の調査へ", "Brewery Investigation"},
    {"砂堀酒造の情報を聞き出せ！", "Get info on the Sunahori Brewery!"},
    {"何を持ちかける？", "What do you Propose?"},
    {"津田沼との共闘", "Tsudanuma's Struggles"},
    {"選択肢", "Choices"},
    {"愚問", "Foolish Question"},
    {"砂堀製品", "Sunahori Products"},
    {"選択肢", "Choices"},
    {"何故わざわざ醤油に", "Why Soy Sauce?"},
    {"死体なら他にも加工可", "Dead Body Process"},
    {"製品にする意味", "To be a Product"},
    {"上手く行ってないみたい", "It's Not Working"},
    {"本庁二課の介入", "Intervention"},
    {"再び砂堀将春と", "With Masaharu Again"},
    {"砂堀に怪しまれず誤魔化しきれ！", "How can we fake it?"},
    {"選択肢", "Choices"},
    {"バレていた", "They Knew"},
    {"殺人に動機", "殺Motive for Murder"},
    {"記者のこと", "Reporters"},
    {"醤油の秘密を", "Soy Sauce Secrets"},
    {"選択肢", "Choices"},
    {"一瞬の出来事", "A Moment in Time"},
    {"蔵の中に", "Warehouse"},
    {"選択肢", "Choices"},
    {"闇の中の扉", "Door in the Dark"},
    {"謎の黒い液体", "Mystery Black Liquid"},
    {"変わり果てた姿", "Disfigured"},
    {"選択肢", "Choices"},
    {"誰がやるか", "Who's going to do it?"},
    {"素直に手伝う", "I'll Help"},
    {"選択肢", "Choices"},
    {"携帯電話を探す", "Find a Cell Phone"},
    {"包丁を探す", "Find a Knife"},
    {"バケツを拾う", "Pickup the Bucket"},
    {"抜け穴を発見", "Loophole"},
    {"選択肢", "Choices"},
    {"そのまま出る", "Keep Going"},
    {"引き返すなんて", "Turning back"},
    {"警戒しながら", "Caution"},
    {"選択肢", "Choices"},
    {"待ち受けるもの", "What to Expect"},
    {"つかの間の安堵", "A Moment's Relief"},
    {"選択肢", "Choices"},
    {"脅しには乗らない", "I don't take kindly to threats"},
    {"承服するしか", "No other Option"},
    {"ダメ元で", "Risk"},
    {"通話終わり", "End of Call"},
    {"死臭の手", "Dead Hand"},
    {"美鈴に悟られる", "Misuzu will know"},
    {"選択肢", "Choices"},
    {"床下より", "From under the floor"},
    {"必死にごまかす", "Desprate to Deceive"},
    {"微笑む", "Smile"},
    {"怒り出す", "Rage"},
    {"結局話す", "We'll talk in the end"},
    {"特ラ課の決起", "Special Agent Decission"},
    {"檻の中と外", "In/Out of the cage"},
    {"対決の場へ", "Showdown"},
    {"推理ロジック", "Inference Logic"},
    {"全てが遅く", "Slow"},
    {"再び対峙", "Confronted"},
    {"時間を稼いで砂堀を揺さぶれ！", "Buy us time to get away from Sunahori!"},
    {"血の終焉", "Bloody End"},
    {"現場検証", "On-Scene Inspection"},
    {"極悪の選択", "Diabolical Choice"},
    {"選択肢", "Choices"},
    {"課長を指す", "Section Chief"},
    {"風守さんを", "Kazamori"},
    {"美鈴を指す", "Misuzu"},
    {"人殺しの餐宴", "Murderer's Banquet"},
    {"寄生虫の金谷大夢", "The Parasite, Kanaya"},
    {"調査手配", "Investigation"},
    {"選択肢", "Choices"},
    {"女々しさ", "Femininity"},
    {"助けを求める応援部署", "Backup department for help"},
    {"出発支度", "Departure"},
    {"死の舞踏", "Danse Macabre"},
    {"夜道の人形", "Doll in the Night"},
    {"人形の呪い", "Doll's Curse"},
    {"人形を確認できるように頼め！", "Ask them to check the doll!"},
    {"美鈴折れる", "Misuzu Breaks"},
    {"人形との対面", "Face-to-face with the Doll"},
    {"介護施設へ", "To the Nursing Home"},
    {"人形の消失", "Doll's Disappearance"},
    {"選択肢", "Choices"},
    {"失礼ね！", "Excuse me!"},
    {"わからない", "I don't know"},
    {"勘違いじゃないの？", "Your mistaken"},
    {"カメラチェック", "Camera Check"},
    {"署内の惨劇", "A Tragedy"},
    {"犯人は人形？", "The Killer's a Doll"},
    {"徒労の作業", "Laborious Task"},
    {"惨劇の酒造", "The Tragic Brewery"},
    {"選択肢", "Choices"},
    {"署に連絡を", "Call the station"},
    {"人形を確保に", "Secure the doll"},
    {"この場から離脱", "I'm out of here"},
    {"そして対面", "Face-to-face"},
    {"呪いの報告", "Report of a Curse"},
    {"黒田に人形の調査を了承させろ！", "Get Kuroda to agree to investigate the doll!"},
    {"しかし一蹴", "Rejection"},
    {"捜査の了承", "Approval"},
    {"再び牧村の元へ", "Back to Makimura"},
    {"呪いの術式", "The Art of the Curse"},
    {"選択肢", "Choices"},
    {"何故亘が？", "Why Watari?"},
    {"亘を殺す理由は？", "Why would he kill Watari?"},
    {"選択肢", "Choices"},
    {"黒田課長が犯人？", "Chief Kuroda is the culprit?"},
    {"風守さんが犯人？", "Kazamori is the killer?"},
    {"牧村さんが犯人？", "Makimura is the killer?"},
    {"足下から奴が", "He came from underneath"},
    {"推理ロジック", "Inference Logic"},
    {"始末屋の音", "Thrifty Sounds"},
    {"聞きたいこと", "I want to ask"},
    {"黒田が事件に関与したか見極めろ！", "Determine if Kuroda was involved in the incident!"},
    {"近付く物音", "Approaching Sounds"},
    {"黒田の豹変", "Kuroda's Change of Heart"},
    {"フカシは禁物", "Don't do anything rash"},
    {"母屋２Ｆ", "Main building 2nd floor"},
    {"大脱出", "The Great Escape"},
    {"振り出しに戻る", "To the Beginning"},
    {"応答ゲーム", "Response Games"},
    {"立花に状況を確認せよ！", "Check with Tachibana, see what's going on!"},
    {"総括", "Generalize"},
    {"浮かぶ疑問", "The one Question"},
    {"熱消毒", "Thermal Disinfection"},
    {"逃避行", "Escape Route"},
    {"立ち位置の確認", "Confirmation of Standing Position"},
    {"津田沼からの誘い", "Invitation from Tsudanuma"},
    {"選択肢", "Choices"},
    {"旅館の失踪事件", "Missing Inn"},
    {"異変", "Accident"},
    {"絶望", "Despair"},
    {"贖罪", "Atonement"},
    {"選択肢", "Choices"},
    {"生存者２名", "Survivor 2"},
    {"生存者１名", "Survivor 1"},
    {"発信者", "Originator"},
    {"関本に金谷救出を納得させろ！", "Convince Sekimoto to rescue Kanaya!"},
    {"地獄の光景", "A scene from hell"},
    {"推理ロジック", "Inference Logic"},
    {"帰還", "Return"},
    {"折れた矢", "Broken Arrow"},
    {"死を回避する取引をせよ！", "Make the deal that averts death!"},
    {"始末", "The Beginning and End"},
    {"炎の村", "Village of Fire"},
    {"忘れ物", "Forget-me-nots"},
    {"選択肢", "Choices"},
    {"ただの悪戯なら", "If this is a prank"},
    {"検討はすべき", "Consider it"},
    {"事件性はあります", "We've got a case"},
    {"興味のない関本", "Uninterested"},
    {"風守の不在", "The Absence of Kazamori"},
    {"選択肢", "Choices"},
    {"チェーンメールを", "Chain Mail"},
    {"週刊サラリー", "Weekly Salary"},
    {"現れる金谷", "Manifestation"},
    {"そして旅館に", "To the Inn"},
    {"金谷旅館の由来", "Origin of Kanaya Inn"},
    {"洞窟の離れ", "Hidden Grotto"},
    {"選択肢", "Choices"},
    {"何を言いかけたの", "What were you about to say?"},
    {"脅迫について", "Intimidation"},
    {"お仕事は楽しい？", "Do you enjoy your work?"},
    {"そして狂宴へ", "Madness"},
    {"立ち塞がる男", "Standing in the Way"},
    {"津田沼に説得を試みろ！", "Try to talk sense into Tsudanuma!"},
    {"命の選択を", "Choose life"},
    {"選択肢", "Choices"},
    {"永久に囚われて", "Trapped Forever"},
    {"不意の一撃に", "Surprise Blow"},
    {"繋がらないコール", "Disconnected Calls"},
    {"激痛", "Violent Pain"},
    {"無柵の檻", "Unfenced Cage"},
    {"最悪の朝", "Worst Morning Ever"},
    {"嫁に来ないか", "Will you Marry Me?"},
    {"選択肢", "Choices"},
    {"しない", "Shinai"},
    {"心に刃を向けてでも", "Even with a Sword in my Heart"},
    {"安堵と油断", "Relief and Carelessness"},
    {"中央ブリーフ連盟", "Central Briefing Federation"},
    {"切り株映像", "Stump Videos"},
    {"金谷の凶行を食い止めろ！", "Put a stop to Kanaya's murder!"},
    {"その選択を", "Make that choice"},
    {"選択肢", "Choices"},
    {"生け贄の祭殿", "Hall of Sacrifice"},
    {"その場逃れに", "Trying to stay out of the way"},
    {"選択肢", "Choices"},
    {"ライアーズブライド", "Liar's Bride"},
    {"優子の知ること", "What Yuuko Knows"},
    {"選択肢", "Choices"},
    {"優子の事情を", "Yuuko's Situation"},
    {"優子を罵る", "Cursing Yuuko"},
    {"優子に同情", "Pity Yuuko"},
    {"如菩薩団", "A Buddist Group"},
    {"風守の末路", "Kazemori's End"},
    {"デッドバイドーン", "Dead By Dawn"},
    {"選択肢", "Choices"},
    {"死ぬには足りない？", "Not good enough to die?"},
    {"死への旅路", "Journey to Death"},
    {"絶望と逆境からの光明", "Sunshine from Despair"},
    {"選択肢", "Choices"},
    {"最後の煩悶", "The Last Agony"},
    {"勝負に出る", "Take a Chance"},
    {"選択肢", "Choices"},
    {"蛇に飲まれるように", "As if Swallowed by a Snake"},
    {"津田沼を言い包めて難を逃れろ！", "Get out of trouble by talking down Tsudanuma!"},
    {"生死のジャンケン", "Rock, Paper, Scissors"},
    {"選択肢", "Choices"},
    {"何とか生存", "How To Survive"},
    {"どうにか生存", "Surviving Somehow"},
    {"負けて死ぬ", "lose and die"},
    {"解き放つ狂気×狂気", "Unleashing Madness x Madness"},
    {"推理ロジック", "Inference Logic"},
    {"命脈尽きて", "dying for dear life"},
    {"ブラッドリィウェディング", "Bloody Wedding"},
    {"選択肢", "Choices"},
    {"結婚はしない", "I'm not getting married"},
    {"くたばれ豚野郎", "Fuck you, you pig"},
    {"ニードルマニアック", "Needle Maniac"},
    {"見詰める金谷", "Staring"},
    {"死の彷徨", "Wandering of the dead"},
    {"ヴィデオ・ドローム", "Video Drome"},
    {"課長との再会", "Reunion with the Chief"},
    {"惨劇の終焉", "The End of the Scourge"},
    {"ザ・ビギニング", "The Beginning"},
    {"無人の警察", "Unattended"},
    {"死屍累々の場", "Scene of Carnage"},
    {"選択肢", "Choices"},
    {"決死の説得", "Desperate Persuasion"},
    {"逃げるしかない！？", "We have to get away!"},
    {"陥る窮地", "Unfavorable Situation"},
    {"この場からの脱出", "Escape This Place"},
    {"集団感染者", "Infected People"},
    {"瀕死の黒田課長", "The dying Chief Kuroda"},
    {"やけになった風守を冷静にさせろ！", "Get the desperate Kazamori to calm down!"},
    {"もはや冷静では……", "I'm no longer calm"},
    {"選択肢", "Choices"},
    {"どかない", "Unsettled"},
    {"どうぞどうぞ", "Here you go"},
    {"キレてみる", "I'm gonna snap"},
    {"選択肢", "Choices"},
    {"死角からの手", "Blind Spot"},
    {"潜む者の闇音", "The Dark Sound of Lurkers"},
    {"忘れ去られた男", "The Forgotten Man"},
    {"フロリダ・ゾンビ", "Florida Zombie"},
    {"蠢く者たちの夜明け", "Dawn of the Wriggling Ones"},
    {"惨劇の旅館", "Scourge of the Inn"},
    {"銃には頼れない", "We can't rely on guns"},
    {"感染者の処理方法", "How to handle infected people"},
    {"映像を信じる金谷を問いただせ！", "Ask Kanaya if he believes the footage!"},
    {"最悪なオススメ", "Worst Recommendation"},
    {"選択肢", "Choices"},
    {"追いかける", "Persue"},
    {"再びの対面", "Face-to-face Again"},
    {"引き止める", "Restrain"},
    {"選択肢", "Choices"},
    {"予行演習", "Exercises"},
    {"感染者狩り", "Hunting for Infected People"},
    {"地獄が溢れる", "Hell is Overflowing"},
    {"そして発症者", "Onset"},
    {"選択肢", "Choices"},
    {"役目は委ねられる", "The role will be Delegated"},
    {"懇願をしても……", "Make a plea"},
    {"そこからの逃避", "Escape"},
    {"猫撫で声", "Wheedling Voice"},
    {"家族の終焉", "The End of the Family"},
    {"消耗する日々", "Exhausting Days"},
    {"介護施設に向かう決意をさせろ！", "Make him determined to head for the nursing home!"},
    {"無茶に挑む", "Challenge"},
    {"選択肢", "Choices"},
    {"関本で", "Sekimoto"},
    {"じゃあ金谷さんで", "Kanaya"},
    {"多勢に無勢", "Outnumbered"},
    {"脱出計画", "Escape Plan"},
    {"出撃", "Battle"},
    {"誰を信じれば？", "Who to Trust"},
    {"選択肢", "Choices"},
    {"推理ロジック", "Inference Logic"},
    {"私の選択", "My Choices"},
    {"地獄のような光景", "A Hellish Scene"},
    {"選択は一つだけ", "Only One Choice"},
    {"最後の願い", "Final Wishes"},
    {"これから先は", "From here on out"},
    {"選択肢", "Choices"},
    {"お店って", "A Store?"},
    {"鳴き声って", "Whats that sound?"},
    {"あなたって", "Who are you?"},
    {"約束", "Promise"},
    {"楽園", "Paradise"},
    {"エデンの入り口", "Entrance to Eden"},
    {"機動隊", "Riot Police"},
    {"懇願", "Pettition"},
    {"ＮＫＰへの潜入捜査を拒絶しろ！", "Refuse to go undercover in the NKP!"},
    {"プランＢ", "Plan B"},
    {"選択肢", "Choices"},
    {"二人で奮闘", "Struggling Together"},
    {"お払い箱", "Fired"},
    {"採用の理由", "Reason for Adoption"},
    {"開き直り", "Opening Up"},
    {"潜入", "Infiltration"},
    {"選択肢", "Choices"},
    {"退路断つ", "Cut off Retreat"},
    {"邪魔者は排除", "Remove those who stand in your way"},
    {"負ける", "Lose"},
    {"妥協", "Compromise"},
    {"ヒロムたんを上手に接客せよ！", "Treat Hiromu-tan Well!"},
    {"新人研修", "Newcomer Training"},
    {"選択肢", "Choices"},
    {"貴重な経験", "Valuable Experience"},
    {"酷い不始末", "Terrible Mismanagement"},
    {"新人の頃", "When I was a Rookie"},
    {"謎の接客術", "Customer Service"},
    {"フェロモン", "Pheromone"},
    {"怪しむ砂堀をやり込めろ！", "Put a stop to the suspicious Sunahori!"},
    {"全身麻痺の不安感", "Full Body Paralysis"},
    {"最深部", "Depest Parts"},
    {"推理ロジック", "Inference Logic"},
    {"楽園ＮＫＰ", "Paradise NKP"},
    {"あともう一息", "One More Sigh"},
    {"感情を見せない男", "Emotionless Man"},
    {"カツ丼とは？", "What is Katsudon?"},
    {"カツ丼の効果", "Effects of Katsudon"},
    {"暴行目撃", "Assault Witness"},
    {"選択肢", "Choices"},
    {"虐待でしょう？", "Abusive, isn't it?"},
    {"拷問なんじゃ？", "Isn't that torture?"},
    {"見なかった事に", "Look the other way"},
    {"そのシステム", "That System"},
    {"黒田との問答", "Q&A with Kuroda"},
    {"黒田らの違法行為を糾弾せよ！", "Condem Kuroda's Illgal Activities!"},
    {"進退問題", "In & Out Questions"},
    {"選択肢", "Choices"},
    {"辞めてやる", "I'm Quitting"},
    {"犯行の証拠写真", "Photo evidence of the crime"},
    {"電気ビリビリ", "Electric Shock"},
    {"選択肢", "Choices"},
    {"スイッチに触れる", "Touching the Switch"},
    {"それは無理", "I can't do that"},
    {"電気拷問", "Electro Torture"},
    {"選択肢", "Choices"},
    {"スイッチを入れ……", "Switch on "},
    {"スイッチ入れません", "Refuse to switch it on"},
    {"電気刑", "Electric Penalty"},
    {"選択肢", "Choices"},
    {"やるしかないのか", "You have to do it"},
    {"電気昇天", "Electrical Phenomena"},
    {"一線超える", "Cross a Line"},
    {"ビリビリいこうぜ", "let's get Cracking"},
    {"関本に説得", "Persuade Sekimoto"},
    {"選択肢", "Choices"},
    {"命だいじに", "Cherish your life!"},
    {"死にますよ", "You're gonna die"},
    {"何を考えて", "What were you thinking?"},
    {"最後の言葉", "Last Words"},
    {"拷問道具", "Torture Props"},
    {"拷問の強要に立ち向かえ！", "Stand up to the torture coercion!"},
    {"何とか言うなら", "Whatever you say"},
    {"選択肢", "Choices"},
    {"辞めさせてもらいます", "I'm Resigning"},
    {"最後のチャンス", "Last Chance"},
    {"美鈴に相談", "Talk to Misuzu"},
    {"相談相手は消される", "Your advisor will be erased"},
    {"選択肢", "Choices"},
    {"逃げるんだ", "We gotta go"},
    {"闇の更にその奥底に", "Deep in the Darkness"},
    {"観念完了", "Contemplation"},
    {"最後の抵抗", "The Last Resistance"},
    {"拷問の強要に抵抗しろ！", "Resist the Torture!"},
    {"拷問するのとされるのと", "To Torture and to be Tortured"},
    {"選択肢", "Choices"},
    {"やるしかないの？", "Do I have to?"},
    {"身体で理解？", "Physical Understanding?"},
    {"じゃあドリルで", "Then Drill"},
    {"ドリルの力", "Power of Drill"},
    {"殺っちゃった", "I killed him"},
    {"リフレイン", "Refrain"},
    {"推理ロジック", "Inference Logic"},
    {"そして再び……", "And again"},
    {"笑う殺人者", "Laughing Murderer"},
    {"美鈴との対決", "Confrontation with Misuzu"},
    {"仕込めるのは誰？", "Who can we plant?"},
    {"食い下がり", "Lost Livelihood"},
    {"特ラ課出動", "Special Agent in Charge"},
    {"対策本部設立", "Establishment"},
    {"ひ……人殺し", "No Murderer"},
    {"急転", "Sudden Change"},
    {"津田沼を上手くコントロールせよ！", "Control Tsudanuma well!"},
    {"生命の危機", "Life-Threatening"},
    {"かぶりつき", "Front Row"},
    {"悪あがき", "Vain Struggle"},
    {"救急車", "Ambulance"},
    {"失敗", "Blunder"},
    {"鏡の中の私", "Me in the Mirror"},
    {"最後の友達", "My last friend"},
    {"唐突の来訪", "An unexpected visit"},
    {"唐突に襲いかかる", "Suddenly it hits me"},
    {"死霊の再訪", "Revisiting the Dead"},
    {"心配なの", "I'm worried"},
    {"泣き喚いて", "Crying"},
    {"黒いもやが這う", "A black miasma crawls"},
    {"血の終焉", "The End of Blood"},
    {"一瞬の出来事", "A Moment in Time"},
    {"素直に手伝う", "I'll help you"},
    {"待ち受けるもの", "What to Expect"},
    {"全てが遅く", "Everything's slow"},
    {"人殺しの餐宴", "Murderer's Banquet"},
    {"惨劇の終焉", "End of the Scourge"},
    {"永久に囚われて", "Trapped forever"},
    {"生け贄の祭殿", "Hall of Sacrifice"},
    {"死への旅路", "Journey to Death"},
    {"蛇に飲まれるように", "Swallowed by a snake"},
    {"負けて死ぬ", "Lose and Die"},
    {"命脈尽きて", "Dying for your life"},
    {"これから先は", "From here on out"},
    {"死角からの手", "Blind Spot"},
    {"再びの対面", "Face to face again"},
    {"そこからの逃避", "Escape from it"},
    {"多勢に無勢", "Outnumbered"},
    {"私の選択", "My Choice"},
    {"選択は一つだけ", "There's only one choice"},
    {"そして再び……", "And again"},
    {"辞めてやる", "I'm quitting"},
    {"電気昇天", "Electrical Phenomena"},
    {"辞めさせてもらいます", "I'm resigning"},
    {"闇の更にその奥底に", "Deeper Into Darkness"},
    {"身体で理解？", "Physical Understanding?"},
    {"笑う殺人者", "Laughing Murderer"},
    {"忘れ物", "Lost Article"},
    {"助けを求める応援部署", "Backup"},
    {"絶望", "Despair"},
    {"贖罪", "Atonement"},
    {"生存者１名", "Survivor 1"},
    {"折れた矢", "Broken Arrow"},
    {"始末", "The Beginning and End"},
    {"黒田の豹変", "Kuroda's change of heart"},
    {"この場から離脱", "I'm out of here"},
    {"しかし一蹴", "Rejection"},
    {"足下から奴が", "He's under our feet"},
    {"始末屋の音", "Thrifty Sounds"},
    {"近付く物音", "Approaching Sounds"},
    {"楽園ＮＫＰ", "Paradise NKP"},
    {"採用の理由", "Reason for Adoption"},
    {"負ける", "Succumb"},
    {"新人の頃", "When I was a rookie"},
    {"全身麻痺の不安感", "Full Body Paralysis"},
    {"あともう一息", "One More Breath"}
};

std::vector<Text> Tree4C {
    {"疑問を口にしてみる", "I'm going to speak my mind"},
    {"皮肉を言う", "speak cynically"},
    {"答えなさい！", "Answer me!"},
    {"関本に会いに行く", "I'm going to see Sekimoto"},
    {"刑事告訴ものです", "That's a criminal complaint"},
    {"怒る", "Get Angry"},
    {"疑問を口にしてみる", "I'm going to speak my mind"},
    {"言葉を飲み込んだ", "Swallowed Words"},
    {"刑事告訴ものです", "That's a criminal complaint"},
    {"怒る", "Get Angry"},
    {"取引に乗る", "Get in on the deal"},
    {"殺し方がずさん", "Sloppy killing"},
    {"単独で飛び込む", "Dive in Solo"},
    {"風守さんを見た", "I saw Kazamori"},
    {"胸を押さえる", "Clutch your chest"},
    {"喜ぶ", "Be Delighted"},
    {"やらせて下さい", "Let me do it"},
    {"尋問を強行する", "Force the Interrogation"},
    {"救急車を呼ぶ", "Call an ambulance"},
    {"喜びだ", "Pleasure"},
    {"連続殺人事件", "Serial Killer"},
    {"思わず口を抑えた", "Hold my Tongue"},
    {"モニターを見つめた", "I stared at the monitor"},
    {"風守さんを見た", "I saw Kazamori"},
    {"休憩所", "Rest Area"},
    {"特ラ課オフィス", "Special Section Office"},
    {"では頂きます", "Let's eat"},
    {"偽物", "Counterfeit"},
    {"根気よく待つ", "Wait patiently"},
    {"やる", "Do it"},
    {"だからこそ出番だ", "That's why you're here"},
    {"あのさ……今なにをしたの？", "what did you just do?"},
    {"真相を話して", "Tell me the truth"},
    {"懇願する", "I beg you"},
    {"もやを払いのける", "Dispel Doubts"},
    {"ただのデタラメ", "Just bullshit"},
    {"情報交換をしたい", "Exchange information"},
    {"わざわざ醤油にする意味は？", "The point of soy sauce"},
    {"殺人に動機がある", "Motive for murder"},
    {"カマをかけてみる", "Try to trick him"},
    {"扉を開ける", "Open the door"},
    {"素直に手伝う", "I'll help you"},
    {"携帯電話を探す", "Find a cell phone"},
    {"そのまま出る", "Keep going"},
    {"一気に外に", "All out at once"},
    {"脅しには乗らない！", "I don't take kindly to threats!"},
    {"必死にごまかす", "desperately try to deceive"},
    {"黒田", "Kuroda"},
    {"現場に急行する", "Rush to the scene"},
    {"失礼ね！", "Excuse me!"},
    {"署に連絡", "Contact the station"},
    {"生みの親である亘はなぜ死んだのか？", "Why did Watari, their birth mother, die?"},
    {"黒田", "Kuroda"},
    {"自分で飲んだ", "I drank it"},
    {"情けをかける", "Show Mercy"},
    {"ただのイタズラ？", "Just a prank?"},
    {"風守にモーニングコール", "Kazamori's Wake-up call"},
    {"何を言いかけたの？", "What were you going to say?"},
    {"諦める", "Resign Oneself"},
    {"しない", "Bamboo Sword"},
    {"イヤ", "No"},
    {"首を横に振る", "Shake your head"},
    {"優子の事情を聞き出す", "Find out what happened to Yuuko"},
    {"鴨居で首をつる", "Hang from the lintel"},
    {"何かの合言葉？", "Code word?"},
    {"誰かの名前？", "Someone's name?"},
    {"グー", "Rock"},
    {"結婚はしない", "I'm not getting married"},
    {"呼びかける", "Call out"},
    {"どかない", "Unsettled"},
    {"冷静になろう", "Let's be cool"},
    {"追いかける", "Chase"},
    {"息を呑む", "Catch your breath"},
    {"金谷に思いとどまらせる", "Dissuade Kanaya"},
    {"関本", "Sekimoto"},
    {"開ける", "Open"},
    {"お店ってなんですか", "What's a store?"},
    {"じゃあ別の角度から捜査を続けます", "Continue from another angle"},
    {"帰るわけにはいかないんです", "I can't just leave"},
    {"遥さんも最初は失敗したんですか？", "Did Haruka fail at first, too?"},
    {"虐待でしょう？", "Abuse, right?"},
    {"辞める", "Quit"},
    {"スイッチを入れる", "Turn on the switch"},
    {"スイッチを入れる", "Turn on the switch"},
    {"やる", "Do it"},
    {"命を大事にして下さい", "Cherish your life"},
    {"辞めさせてもらいます", "I'm Resigning"},
    {"逃げ出す", "Escape"},
    {"やる", "Do it"}
};

std::vector<Text> Tree8C {
    {"怒らせてみる", "I'll try to make him angry"},
    {"しかりつける", "Scold Harshly"},
    {"私の負けよ", "I've lost"},
    {"その必要はない", "No need for that"},
    {"復讐をするでしょう", "He'll have his revenge"},
    {"騒ぐ", "Be noisy"},
    {"怒らせてみる", "I'll try to make him angry"},
    {"皮肉を言う", "Speak Cynically"},
    {"民事賠償ものです", "Civil damages"},
    {"騒ぐ", "Be Noisy"},
    {"取引を蹴る", "Refuse the deal"},
    {"全裸じゃない", "They're not naked"},
    {"応援を呼ぶ", "Call for backup"},
    {"後ずさった", "They're Backpedaling"},
    {"口を押さえる", "Hold my tongue"},
    {"驚く", "Be Surprised"},
    {"風守さんの死を無駄にしないで下さい", "Don't let His death be in vain"},
    {"諦める", "Give up"},
    {"署からの応援を急がせる", "Get backup from the station ASAP"},
    {"恐怖だ", "Be Afraid"},
    {"ブラインドマン", "Blind Man"},
    {"現場に向かった", "We're on our way"},
    {"思わず口を抑えた", "Hold my Tongue"},
    {"後ずさった", "He fell back"},
    {"特ラ課オフィス", "Special Section Office"},
    {"留置所", "Jail"},
    {"公務中なので無理", "I can't I'm on official business"},
    {"偶然", "Accident"},
    {"疑ってはいない", "I don't doubt it"},
    {"やらない", "I don't do it"},
    {"諦める", "Give Up"},
    {"まさか……見えているの？", "Don't tell me you can see?"},
    {"疑ってるの", "I doubt it"},
    {"泣き喚く", "Bawl"},
    {"応援を呼ぶ", "Call for backup"},
    {"それは風評被害", "It's a rumor"},
    {"何か他に隠してる？", "Is there something else you're not telling me?"},
    {"死体の隠滅なら他にも……", "If you want to hide a body, here's something else"},
    {"記者のこと", "Reporters"},
    {"黙っていよう", "I'll keep my mouth shut"},
    {"逃げる手を考える", "Think of a way out"},
    {"誰がやるか！", "Who'll do it!"},
    {"包丁を探す", "Find a knife"},
    {"引き返す", "Retrace one's steps"},
    {"注意を払う", "Pay Attention"},
    {"……わかったわ", "I figured out"},
    {"微笑む", "Smirk"},
    {"風守", "Kazamori"},
    {"捜査一課に応援要請", "Requesting Backup"},
    {"わからない", "I don't know"},
    {"人形を確保", "Secure the doll"},
    {"亘を殺す理由は？", "Why would he kill Watari?"},
    {"風守", "Kazamori"},
    {"風守さんに飲むよう求めた", "I asked Kazamori to drink"},
    {"ここで恨みを晴らす", "I'll settle my grudge here"},
    {"検討はすべき", "Consider it"},
    {"風守にチェーンメール", "Kazamori's Chain Mail"},
    {"脅迫について何か知っているの？", "What do you know about blackmail?"},
    {"悲鳴をあげる", "Scream"},
    {"考えさせて", "Let me think"},
    {"そうでない", "Not really"},
    {"うなずく", "Nod"},
    {"優子を罵る", "Cursing Yuuko"},
    {"ドアノブで首をつる", "Hung by the doorknob"},
    {"店の名前？", "The name of the store?"},
    {"ビデオ店？", "Video store?"},
    {"チョキ", "Scissors"},
    {"くたばれ豚野郎", "Fuck you, you pig"},
    {"逃げ出す", "Escape"},
    {"どうぞどうぞ", "Here you go"},
    {"ガラスを片付けて", "Clear the glass"},
    {"引き止める", "Restrain"},
    {"人殺し！？", "Murderer!?"},
    {"風守にやめさせるように懇願する", "Beg Kazamori to stop"},
    {"金谷", "Kanaya"},
    {"開けない", "Can't open"},
    {"にゃんにゃんってなんですか", "What's a nyannyan?"},
    {"これで私はお役御免ですね", "I guess I'm off the hook now"},
    {"邪魔すると逮捕しますよ", "If you interfere, I'll arrest you"},
    {"コツとかあるんですか？", "Do you have any tips or tricks?"},
    {"拷問なんじゃ？", "Isn't that torture?"},
    {"文句を付ける", "lodge a complaint"},
    {"スイッチを入れない", "I'm not turning it on"},
    {"スイッチを入れない", "I'm not turning it on"},
    {"やらない", "I don't do it"},
    {"供述しないと死にますよ", "If you don't give a statement, you'll die"},
    {"それより責任問題は？", "What about liability?"},
    {"叫ぶ", "Scream"},
    {"体で理解", "Understanding through the body"}
};

std::vector<Text> TreeCC {
    {"彼に興味はある？", "Are you interested in him?"},
    {"観察する", "Observe"},
    {"しかりつける", "Scold harshly"},
    {"復讐をするでしょう", "He will have his revenge"},
    {"おどける", "Joke"},
    {"歯が残っている", "Teeth still intact"},
    {"様子を見る", "wait and see"},
    {"話しかける", "Speak up"},
    {"怖がる", "Fear"},
    {"見くびらないで下さい", "Don't underestimate me"},
    {"応急処置を行う", "Provide first aid"},
    {"笑いだ", "Laughter"},
    {"水瀬遥殺人事件", "Minase's Murder"},
    {"現場に向かった", "I'm on my way to the scene"},
    {"力の限り叫んだ", "I screamed as hard as I could"},
    {"留置所", "Jail"},
    {"友達だと思って", "Think of me as a friend"},
    {"もう少し考える", "I'll think about it some more"},
    {"えっと……どうかしたの？", "Um what's wrong?"},
    {"心配なの", "I'm worried"},
    {"製品にする意味がない", "There is no point in making a product"},
    {"醤油の秘密", "Secrets of Soy Sauce"},
    {"バケツを拾う", "Pick up the bucket"},
    {"警戒する", "be cautious"},
    {"考えさせて", "Let me think"},
    {"怒り出す", "fly into a rage"},
    {"立花", "Woman"},
    {"もう一度電話をかける", "I'll call you back"},
    {"勘違いじゃないの？", "I think you're mistaken"},
    {"脱出", "Escape"},
    {"この人形に呪いを仕込めるのは誰だ？", "Who can put a curse on this doll?"},
    {"牧村", "Makimura"},
    {"黒田課長に飲ませる事にした", "I've decided to give it to Chief Kuroda"},
    {"事件性はある", "We have a case"},
    {"お仕事は楽しい？", "Do you enjoy your work?"},
    {"助けを呼ぶ", "I'll get help"},
    {"優子に同情する", "I feel sorry for Yuuko"},
    {"パー", "Paper"},
    {"立ち向かう", "face"},
    {"キレる", "lose one's temper"},
    {"砂堀に逃げるように叫ぶ", "Telling Kazamori to run away"},
    {"あなた大丈夫ですか", "Are you okay?"},
    {"最初からそれを採用すればいいのに", "Why not just adopt that from the start?"},
    {"私に負けるから怖いんでしょ", "You're afraid I'll beat you"},
    {"叱らないんですか？", "You're not going to scold me?"},
    {"見なかった事に", "pretend I didn't see it"},
    {"何を考えているんですか？", "What do you have in mind?"},
    {"本当にやるの？", "Are you sure you want to do this?"},
    {"観念する", "Contemplate"}
};
