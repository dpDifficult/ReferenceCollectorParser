# Unity ET框架下的ReferenceCollector解析器

该解析器用于在Unity的ET框架中解析Prefab中的ReferenceCollector组件，并生成对应的C#代码。该代码用于访问Prefab中包含ReferenceCollector组件和名称带有“Form”的对象。

## 示例


当将项目窗口中的Prefab拖入时，该解析器会自动解析Prefab中含有ReferenceCollector组件和名称带有“Form”的对象，并生成以下形式的C#代码：

```csharp
// ShopForm
public GameObject Tabs4;
public GameObject Content;
public Button ZD;
public GameObject Scroll;
public Button CloseBtn;
public Image HonorImg_1;
public Text HonorTex_1;
public Image HonorImg_2;
public Text HonorTex_2;

// ShopFormSystem
self.Tabs4 = self.Collector.Get<GameObject>("Tabs4");
self.Content = self.Collector.Get<GameObject>("Content");
self.ZD = self.Collector.Get<Button>("ZD");
self.Scroll = self.Collector.Get<GameObject>("Scroll");
self.CloseBtn = self.Collector.Get<Button>("CloseBtn");
self.HonorImg_1 = self.Collector.Get<Image>("HonorImg_1");
self.HonorTex_1 = self.Collector.Get<Text>("HonorTex_1");
self.HonorImg_2 = self.Collector.Get<Image>("HonorImg_2");
self.HonorTex_2 = self.Collector.Get<Text>("HonorTex_2");

### 缺点
1.无法解析包含Prefab的子Prefab，因为数据在子Prefab中。
2.想要新增类型时，需要手动在Script.cpp中添加对应的哈希表。
