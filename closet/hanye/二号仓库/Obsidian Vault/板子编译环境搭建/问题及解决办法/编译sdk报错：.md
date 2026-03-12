
![[img_v3_02b2_4009b33c-ffa0-4a28-abbb-5f8d044eaedg.jpg]]
./build.sh --product-name ohos-sdk --ccache报错

解决方案：
尝试方式：重新编译：
```
./build.sh --product-name ohos-sdk

```

编译还是报错：删除out文件夹：
rm -r out

重新编译
![[Pasted image 20240521085813.png]]