这是一个Unity的ET框架下的对于ReferenceCollector的一个解析器，将project窗口中的prefab拖入，自动解析其中含有ReferenceCollector组件和名称带有“Form”的对象并生成形如以下的C#代码：
ShopForm :
public GameObject Tabs4;
public GameObject Content;
public Button ZD;
public GameObject Scroll;
public Button CloseBtn;
public Image HonorImg_1;
public Text HonorTex_1;
public Image HonorImg_2;
public Text HonorTex_2;

ShopFormSystem :
self.Tabs4 = self.Collector.Get<GameObject>("Tabs4");
self.Content = self.Collector.Get<GameObject>("Content");
self.ZD = self.Collector.Get<Button>("ZD");
self.Scroll = self.Collector.Get<GameObject>("Scroll");
self.CloseBtn = self.Collector.Get<Button>("CloseBtn");
self.HonorImg_1 = self.Collector.Get<Image>("HonorImg_1");
self.HonorTex_1 = self.Collector.Get<Text>("HonorTex_1");
self.HonorImg_2 = self.Collector.Get<Image>("HonorImg_2");
self.HonorTex_2 = self.Collector.Get<Text>("HonorTex_2");

--------------------------------------------------------------------------
缺点：
1.它对于prefab中包含prefab无法解析，因为数据在子prefab中。
2.对于想要新增类型必须手动的在Script.cpp中添加对应的哈希表。
