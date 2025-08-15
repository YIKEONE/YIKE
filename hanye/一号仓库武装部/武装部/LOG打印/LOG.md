打印指针地址：
```
LOGE("text han onDragEnd, pattern:%{public}p", AceType::RawPtr(pattern));
```

打印枚举值：

```
LOGE("text han %{public}d", static_cast<int32_t>(test));
```

打印函数名:
```
LOGE("###TEST %{public}s IN", __func__);
```

```
LOGE("###TEST %{public}s OUT", __func__);
```

