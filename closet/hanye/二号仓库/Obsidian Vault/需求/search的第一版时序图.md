```
sequenceDiagram
Participant 框架
Participant SearchModelNG
Participant FrameNode
Participant SearchPattern
Participant TextFieldEventHub
Participant RenderContext
Participant EventHub

activate SearchModelNG
SearchModelNG->>FrameNode:GetOrCreateFrameNode()
activate FrameNode
FrameNode-->>SearchModelNG:GetFrameNode()
SearchModelNG->>SearchPattern:SetButtonNode()
activate SearchPattern
activate 框架
框架->>FrameNode:MarkModifyDone()
FrameNode->>SearchPattern:MarkModifyDone()
SearchPattern->>SearchPattern:OnModifyDone()
SearchPattern->>SearchPattern:InitTextFieldValueChangeEvent()

SearchPattern-->>FrameNode:host->GetChildren()
FrameNode->>SearchPattern:GetEventHub()
SearchPattern->>TextFieldEventHub:GetOnChange()
activate TextFieldEventHub
TextFieldEventHub-->>SearchPattern:isOnChange() 布尔类型
deactivate TextFieldEventHub

SearchPattern->>SearchPattern:UpdateChangeEvent()
SearchPattern-->>FrameNode:host->GetOrCreateFrameNode()
FrameNode->>SearchPattern:GetRenderContext()
SearchPattern->>RenderContext:UpdateBackgroundColor()
activate RenderContext
RenderContext-->>SearchPattern:void()
deactivate RenderContext

SearchPattern-->>FrameNode:host->GetOrCreateFrameNode()
FrameNode->>SearchPattern:GetEventHub()
SearchPattern->>EventHub:SetEnabLed()
activate EventHub
EventHub-->>SearchPattern:isEnabLed()布尔类型
deactivate EventHub
deactivate SearchModelNG
deactivate SearchPattern
deactivate FrameNode
deactivate 框架

```