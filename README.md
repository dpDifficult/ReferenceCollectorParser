# Unity ET框架下的ReferenceCollector解析器

该解析器用于在Unity的ET框架中解析Prefab中的ReferenceCollector组件，并生成对应的C#代码。

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
```

## 代码简要设计思路以及各类的作用
遍历一边prefab，获取所有的gameobject

查找：
判断一个gameobject是不是form并判断是否含有ReferenceCollector脚本（gameobject），
ReferenceCollector的脚本上有关于子节点的信息，包括子物体的fileid，这个fileid可以找到该物体以及该物体的monobehavior信息，
如果ReferenceCollector上子节点的信息在其他prefab上，意味着含有target类型，通过mono上的id查找到其中的
m_CorrespondingSourceObject: fileID 在通过这个fileid找到target，target.value就是需要的formname,
在window的文件夹下遍历一边查找target.value，并打开再获取其中的ReferenceCollector上子节点的信息，加入到
GameObject::gameObjectList中。

### GameObject类
从prefab抽象的GameObject，它有多个fileID和多个MonoBehaviour,以及一系列关于查找类型的方法。
包含了GameObject的名字以及类型的信息。
### MonoBehaviour类
主要是包含Script类，从Script类中获取MonoBehaviour的类型，无论如何都会得到最基础的类型GameObject（类型名）。
以及Data类的集合，这个的主要作用是通过其中的fileId找到GameObject。
### Script类
主要作用是返回这个Script实例的类型。无论如何都会得到最基础的类型GameObject（类型名）。
需要增加自定义的类型需要在其cpp文件的hash表中添加数据。

## 新增
现在，该prefab的ReferenceCollecor上有prefab，如果它在同名文件夹下可以找到并一起解析。
使用stringstream和string_view代替了string的拼接或者字串操作，更加高效了一点。

## 缺点
2.想要新增类型时，需要手动在Script.cpp中添加对应的哈希表。
